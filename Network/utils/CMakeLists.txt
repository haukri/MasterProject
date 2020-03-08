add_library (utils Clock.h Clock.cpp Parameters.h Event.h Logging.h Logging.cpp helperFunctions.h)

target_link_libraries(utils Network)
