#ifndef iaf_psc_alpha_H
#define iaf_psc_alpha_H

#include <iostream>
#include "Neuron.h"
#include "Network/utils/Parameters.h"
#include "Network/utils/Clock.h"
#include <limits>

struct iaf_psc_alpha_param : Parameters {
    double Tau_ = 10.0;             // ms
    double C_ = 250.0;              // pF
    double TauR_ = 2.0;             // ms
    double E_L_ = -70.0;            // mV
    double I_e_ = 0.0;              // pA
    double V_reset_ = -70.0 - E_L_; // mV, rel to E_L_
    double Theta_ = -55.0 - E_L_;   // mV, rel to E_L_
    double LowerBound_ = -std::numeric_limits< double >::max();
    double tau_ex_ = 2.0;           // ms
    double tau_in_ = 2.0;           // ms
};

class iaf_psc_alpha : public Neuron
{
public:
    iaf_psc_alpha(long populationID, int neuronID);
    iaf_psc_alpha(long populationID, int neuronID, iaf_psc_alpha_param*);
    Event* update(double);
    void handleEvent(Event*);
    double getMembranePotential();
    void resetInput();
    ~iaf_psc_alpha();
private:
    double propagator_31( double tau_syn, double tau, double C, double h );
    double propagator_32( double tau_syn, double tau, double C, double h );
    void calibrate();
    bool shouldCalibrate = true;
    double dt;
    iaf_psc_alpha_param* param;
    Clock* clock;

    // State
    double y0_ = 0; //!< Constant current
    double dI_ex_ = 0;
    double I_ex_ = 0;
    double dI_in_ = 0;
    double I_in_ = 0;
    double y3_ = 0;
    int r_ = 0; //!< Number of refractory steps remaining

    // Variables
    double EPSCInitialValue_;
    double IPSCInitialValue_;
    int RefractoryCounts_;
    double P11_ex_;
    double P21_ex_;
    double P22_ex_;
    double P31_ex_;
    double P32_ex_;
    double P11_in_;
    double P21_in_;
    double P22_in_;
    double P31_in_;
    double P32_in_;
    double P30_;
    double P33_;
    double expm1_tau_m_;
    double weighted_spikes_ex_;
    double weighted_spikes_in_;

    double ex_spikes_ = 0;
    double in_spikes_ = 0;
};



#endif
