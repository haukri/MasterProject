add_library (utils Clock.h Clock.cpp Parameters.h Event.h)

target_link_libraries(utils Network)
