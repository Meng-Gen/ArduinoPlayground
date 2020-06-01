struct PinConfig {
  byte led = LED_BUILTIN;
  byte switch_button = 8;
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

class SwitchButton {
 public:
  explicit SwitchButton(PinConfig pin_config)
      : pin_config_(pin_config) {
    pinMode(pin_config_.switch_button, INPUT);
  }

  bool IsPressed() {
    return digitalRead(pin_config_.switch_button);
  }

 private:
  PinConfig pin_config_;
};

class ArduinoBoard {
 public:
  explicit ArduinoBoard(PinConfig pin_config)
      : led_(new Led(pin_config))
      , switch_button_(new SwitchButton(pin_config)) {
  }

  void HandleInputs() {
    if (switch_button_->IsPressed()) {
      led_->TurnOn();
    } else {
      led_->TurnOff();
    }
  }

 private:
  Led* led_;
  SwitchButton* switch_button_;
};

ArduinoBoard* arduino_board;

void setup() {
  PinConfig pin_config;
  arduino_board = new ArduinoBoard(pin_config);
}

void loop() {
  arduino_board->HandleInputs();
}
