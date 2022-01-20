#include <IRremote.h>

// управление модулем
int PLAY_pin = 2;
int NEXT_pin = 1;
int PREV_pin = 0;

int PRESS_DELAY = 100;

// ИК приемник
int IR_pin = 3;
IRrecv ir_recv(IR_pin);
decode_results ir_results;

// соответствие кодов кнопок пульта ДУ Sony RMT-CS50AD
// пинам управления модулем
#define RC_CODE_NUMBER 5
unsigned long rc_code_pin_map[RC_CODE_NUMBER][2] =
{{0x2626, PLAY_pin},  // PLAY
 {0x4E26, PLAY_pin},  // PAUSE
 {0x0E26, PLAY_pin},  // STOP
 {0x4626, NEXT_pin},  // NEXT
 {0x0626, PREV_pin}}; // PREV


void setup()
{
  // Serial.begin(9600);
  
  // режим пинов
  pinMode(PLAY_pin, OUTPUT);
  digitalWrite(PLAY_pin, 0);
  pinMode(NEXT_pin, OUTPUT);
  digitalWrite(PLAY_pin, 0);
  pinMode(PREV_pin, OUTPUT);
  digitalWrite(PLAY_pin, 0);
   
  ir_recv.enableIRIn(); // включаем приемник
}


void loop() {
  
  if (ir_recv.decode(&ir_results)) {
    // ждем код от пульта
    //Serial.println(ir_results.value, HEX);
    
    // код принят, ищем в таблице соответствия
    for (int i = 0; i < RC_CODE_NUMBER; i++) {
      if (ir_results.value == rc_code_pin_map[i][0]) {
        // код найден
        // передаем короткий импульс на соотв.пин     
        digitalWrite(rc_code_pin_map[i][1], 1);
        delay(PRESS_DELAY);
        digitalWrite(rc_code_pin_map[i][1], 0);
        
        break;
      }
    }      
    ir_recv.resume(); // продолжаем прием кодов
  }

}
