#include <MqttConnector.h>
  
MqttConnector::prepare_data_hook_t on_prepare_data =
[&](JsonObject * root) -> void {
    float t_dht = 0;
    float h_dht = 0;

    JsonObject& data = (*root)["d"];
    JsonObject& info = (*root)["info"];
    digitalWrite(LED, LOW);
    data["myName"] = DEVICE_NAME;
    data["temp"] = thermocouple.readCelsius();
    digitalWrite(LED, HIGH);
};
