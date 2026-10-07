import json
import paho.mqtt.client as mqtt

from config import MQTT_BROKER, MQTT_PORT, MQTT_TOPIC


class MQTTHandler:

    def __init__(self):

        self.client = None

        try:

            self.client = mqtt.Client()

            self.client.connect(
                MQTT_BROKER,
                MQTT_PORT,
                60
            )

            # MQTT chạy background
            self.client.loop_start()

            print("[MQTT] Da ket noi toi Broker")

        except Exception as e:

            print(f"[MQTT] Khong ket noi duoc: {e}")

            self.client = None


    def publish(self, data):

        if self.client is None:
            return False

        try:

            payload = json.dumps(data)

            result = self.client.publish(
                MQTT_TOPIC,
                payload,
                qos=0,
                retain=False
            )

            if result.rc == mqtt.MQTT_ERR_SUCCESS:

                print(f"[MQTT] {payload}")

                return True

            print(
                f"[MQTT] Publish failed: {result.rc}"
            )

            return False

        except Exception as e:

            print(
                f"[MQTT] Publish error: {e}"
            )

            return False


    def disconnect(self):

        if self.client is not None:

            self.client.loop_stop()

            self.client.disconnect()

            print("[MQTT] Da ngat ket noi")