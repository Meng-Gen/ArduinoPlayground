struct PinConfig {
  byte led = LED_BUILTIN;
};

class Led {
 public:
  explicit Led(PinConfig pin_config)
      : pin_config_(pin_config) {
    pinMode(pin_config_.led, OUTPUT);
  }

  void TurnOn() {
    digitalWrite(pin_config_.led, HIGH);
  }

  void TurnOff() {
    digitalWrite(pin_config_.led, LOW);
  }

 private:
  PinConfig pin_config_;
};

class ArduinoBoard {
 public:
  explicit ArduinoBoard(PinConfig pin_config)
      : led_(new Led(pin_config)) {
  }

  void HandleInputs() {
    led_->TurnOn();
    delay(1000);
    led_->TurnOff();
    delay(1000);
  }

 private:
  Led* led_;
};

ArduinoBoard* arduino_board;

void setup() {
  PinConfig pin_config;
  arduino_board = new ArduinoBoard(pin_config);
}

void loop() {
  arduino_board->HandleInputs();
}
