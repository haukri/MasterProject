#include "iaf_psc_alpha.h"
#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

iaf_psc_alpha::iaf_psc_alpha(long n_populationID, int n_neuronID) : param(new iaf_psc_alpha_param) {
    populationID = n_populationID;
    neuronID = n_neuronID;
    initialize();
}

iaf_psc_alpha::iaf_psc_alpha(long n_populationID, int n_neuronID, iaf_psc_alpha_param* param) : param(param) {
    populationID = n_populationID;
    neuronID = n_neuronID;
    initialize();
}

double iaf_psc_alpha::propagator_31( double tau_syn, double tau, double C, double h )
{
  const double P31_linear = 1 / ( 3. * C * tau * tau ) * h * h * h * ( tau_syn - tau ) * std::exp( -h / tau );
  const double P31 =
    1 / C * ( std::exp( -h / tau_syn ) * std::expm1( -h / tau + h / tau_syn ) / ( tau / tau_syn - 1 ) * tau
              - h * std::exp( -h / tau_syn ) ) / ( -1 - -tau / tau_syn ) * tau;
  const double P31_singular = h * h / 2 / C * std::exp( -h / tau );
  const double de31 = std::abs( P31 - P31_singular );

  if ( tau == tau_syn or ( std::abs( tau - tau_syn ) < 0.1 and de31 > 2 * std::abs( P31_linear ) ) )
  {
    return P31_singular;
  }
  else
  {
    return P31;
  }
}

double iaf_psc_alpha::propagator_32( double tau_syn, double tau, double C, double h )
{
  const double P32_linear = 1 / ( 2. * C * tau * tau ) * h * h * ( tau_syn - tau ) * std::exp( -h / tau );
  const double P32_singular = h / C * std::exp( -h / tau );
  const double P32 =
    -tau / ( C * ( 1 - tau / tau_syn ) ) * std::exp( -h / tau_syn ) * std::expm1( h * ( 1 / tau_syn - 1 / tau ) );

  const double de32 = std::abs( P32 - P32_singular );

  if ( tau == tau_syn or ( std::abs( tau - tau_syn ) < 0.1 and de32 > 2 * std::abs( P32_linear ) ) )
  {
    return P32_singular;
  }
  else
  {
    return P32;
  }
}

void iaf_psc_alpha::calibrate() {
    double h = dt*1000.0;
    
    // these P are independent
    P11_ex_ = P22_ex_ = std::exp(   -h / param->tau_ex_ );
    P11_in_ = P22_in_ = std::exp( -h / param->tau_in_ );

    P33_ = std::exp( -h / param->Tau_ );

    expm1_tau_m_ = std::expm1( -h / param->Tau_ );

    // these depend on the above. Please do not change the order.
    P30_ = -param->Tau_ / param->C_ * std::expm1( -h / param->Tau_ );
    P21_ex_ = h * P11_ex_;
    P21_in_ = h * P11_in_;

    // these are determined according to a numeric stability criterion
    P31_ex_ = propagator_31( param->tau_ex_, param->Tau_, param->C_, h );
    P32_ex_ = propagator_32( param->tau_ex_, param->Tau_, param->C_, h );
    P31_in_ = propagator_31( param->tau_in_, param->Tau_, param->C_, h );
    P32_in_ = propagator_32( param->tau_in_, param->Tau_, param->C_, h );

    EPSCInitialValue_ = 1.0 * M_E / param->tau_ex_;
    IPSCInitialValue_ = 1.0 * M_E / param->tau_in_;

    RefractoryCounts_ = param->TauR_/h;
}

Event* iaf_psc_alpha::update(double n_dt) {
    dt = n_dt;
    if(shouldCalibrate) {
        calibrate();
        shouldCalibrate = false;
    }
    if ( r_ == 0 )
    {
      // neuron not refractory
      y3_ = P30_ * ( y0_ + param->I_e_ ) + P31_ex_ * dI_ex_ + P32_ex_ * I_ex_ + P31_in_ * dI_in_
        + P32_in_ * I_in_ + expm1_tau_m_ * y3_ + y3_;
    
      // lower bound of membrane potential
      y3_ = ( y3_ < param->LowerBound_ ? param->LowerBound_ : y3_ );
    }
    else
    {
      // neuron is absolute refractory
      --r_;
    }


    // alpha shape EPSCs
    I_ex_ = P21_ex_ * dI_ex_ + P22_ex_ * I_ex_;
    dI_ex_ *= P11_ex_;

    // Apply spikes delivered in this step; spikes arriving at T+1 have
    // an immediate effect on the state of the neuron
    weighted_spikes_ex_ = ex_spikes_;
    dI_ex_ += EPSCInitialValue_ * weighted_spikes_ex_;

    // alpha shape EPSCs
    I_in_ = P21_in_ * dI_in_ + P22_in_ * I_in_;
    dI_in_ *= P11_in_;

    // Apply spikes delivered in this step; spikes arriving at T+1 have
    // an immediate effect on the state of the neuron
    weighted_spikes_in_ = in_spikes_;
    dI_in_ += IPSCInitialValue_ * weighted_spikes_in_;


    
    // threshold crossing
    if ( y3_ >= param->Theta_ )
    {
      r_ = RefractoryCounts_;
      y3_ = param->V_reset_;
      // A supra-threshold membrane potential should never be observable.
      // The reset at the time of threshold crossing enables accurate
      // integration independent of the computation step size, see [2,3] for
      // details.
      logger->logValue(populationID, neuronID, ValueType::voltage, y3_ + param->E_L_);
      return new SpikeEvent();
    }
    logger->logValue(populationID, neuronID, ValueType::voltage, y3_ + param->E_L_);
    return new NoEvent();
}

void iaf_psc_alpha::resetInput() {
    in_spikes_ = 0;
    ex_spikes_ = 0;
    y0_ = 0;
}

double iaf_psc_alpha::getMembranePotential() {
    return 0;
};

void iaf_psc_alpha::handleEvent(Event* e) {
    if(e->type == EventType::Spike) {
        double weighted = static_cast<SpikeEvent*>(e)->weight * static_cast<SpikeEvent*>(e)->multiplicity;
        if(weighted > 0.0) {
            ex_spikes_ += weighted;
        }
        else {
            in_spikes_ += weighted;
        }
    }
    else if(e->type == EventType::Current) {
        y0_ += static_cast<CurrentEvent*>(e)->weight * static_cast<CurrentEvent*>(e)->current;
    }
}

iaf_psc_alpha::~iaf_psc_alpha() {
}