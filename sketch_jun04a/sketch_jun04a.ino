#include <IRremote.h>

struct PinConfig {
  byte ir_receiver = 6;
};

class Event {
 public:
  explicit Event(PinConfig pin_config)
      : ir_recv_(new IRrecv(pin_config.ir_receiver))
      , results_(new decode_results()) {
    Serial.println("Enabling IRin");
    ir_recv_->enableIRIn();
    Serial.println("Enabled IRin");
  }

  bool HasEvent() {
    if (ir_recv_->decode(results_)) {
      Serial.println(results_->value, HEX);
      ir_recv_->resume();
      return true;
    }
    return false;
  }

 private:
  IRrecv* ir_recv_;
  decode_results* results_;
};

class ArduinoBoard {
 public:
  explicit ArduinoBoard(PinConfig pin_config)
      : event_(new Event(pin_config)) {
  }

  void HandleInputs() {
    event_->HasEvent();
  }

 private:
  Event* event_;
};

ArduinoBoard* arduino_board;

void setup() {
  Serial.begin(9600);
  PinConfig pin_config;
  arduino_board = new ArduinoBoard(pin_config);
}

void loop() {
  arduino_board->HandleInputs();
  delay(100);
}
