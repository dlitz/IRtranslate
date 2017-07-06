// by Dwayne Litzenberger
// Simulate Danby DPAC5011 IR remote
#include <IRremote.h>

typedef struct {
  struct {
    decode_type_t decode_type;
    unsigned long value;
    int rawlen;
  } in;
  struct {
    unsigned long value;
    int repeat;
  } out;
} xlat_entry;

const xlat_entry xlat_table[] = {
#if 0
  /* TV remote -> HDMI switch */
  { { SAMSUNG, 0xE0E036C9 /* A */, 68 },    { 0x1FE40BF /* 1 */, 3 } },
  { { SAMSUNG, 0xE0E028D7 /* B */, 68 },    { 0x1FE20DF /* 2 */, 3 } },
  { { SAMSUNG, 0xE0E0A857 /* C */, 68 },    { 0x1FEA05F /* 3 */, 3 } },
  { { SAMSUNG, 0xE0E06897 /* D */, 68 },    { 0x1FE609F /* 4 */, 3 } },
  { { SAMSUNG, 0xE0E0629D /* STOP */, 68 }, { 0x1FE10EF /* 5 */, 3 } },
#endif

#if 0
  // Remote: Hauppauge! remote
  { { RC5, 0x781 /* 1 */, 24},         { 0x4FB40BF /* power */, 0 } },
  { { RC5, 0xF81 /* 1 */, 26},         { 0x4FB40BF /* power */, 0 } },
  { { RC5, 0x782 /* 2 */, 22},         { 0x4FB906F /* mode */, 0 } },
  { { RC5, 0xF82 /* 2 */, 24},         { 0x4FB906F /* mode */, 0 } },  
  { { RC5, 0x784 /* 4 */, 22},         { 0x4FB58A7 /* fan speed */, 0 } },
  { { RC5, 0xF84 /* 4 */, 24},         { 0x4FB58A7 /* fan speed */, 0 } },  
  { { RC5, 0x785 /* 5 */, 22},         { 0x4FB50AF /* up */, 0 } },
  { { RC5, 0xF85 /* 5 */, 24},         { 0x4FB50AF /* up */, 0 } },
  { { RC5, 0x787 /* 7 */, 24},         { 0x4FB9867 /* timer */, 0 } },
  { { RC5, 0xF87 /* 7 */, 26},         { 0x4FB9867 /* timer */, 0 } },
  { { RC5, 0x788 /* 8 */, 22},         { 0x4FB8877 /* down */, 0 } },
  { { RC5, 0xF88 /* 8 */, 24},         { 0x4FB8877 /* down */, 0 } },
//  { { RC5, 0x78A /* * */, 20},         { ?          /* cancel timer */, 0 } },
//  { { RC5, 0xF8A /* * */, 22},         { ?          /* cancel timer */, 0 } },
  { { RC5, 0x780 /* 0 */, 24},         { 0x4FB00FF /* celsius/fahrenheit */, 0 } },
  { { RC5, 0xF80 /* 0 */, 26},         { 0x4FB00FF /* celsius/fahrenheit */, 0 } },  

  { { RC5, 0x7BD /* Power */, 22 },    { 0x4FB40BF /* power */, 0 } },
  { { RC5, 0xFBD /* Power */, 24 },    { 0x4FB40BF /* power */, 0 } },
  { { RC5, 0x792 /* Prev Ch */, 20},   { 0x4FB906F /* mode */, 0 } },
  { { RC5, 0xF92 /* Prev Ch*/, 22},    { 0x4FB906F /* mode */, 0 } },  
  { { RC5, 0x78F /* Mute */, 24},      { 0x4FB58A7 /* fan speed */, 0 } },
  { { RC5, 0xF8F /* Mute */, 26},      { 0x4FB58A7 /* fan speed */, 0 } },
  { { RC5, 0x794 /* Up */, 20},        { 0x4FB50AF /* up */, 0 } },
  { { RC5, 0xF94 /* Up */, 22},        { 0x4FB50AF /* up */, 0 } },
  { { RC5, 0x795 /* Down */, 20},         { 0x4FB8877 /* down */, 0 } },
  { { RC5, 0xF95 /* Down */, 22},         { 0x4FB8877 /* down */, 0 } },
  { { RC5, 0x790 /* Vol Up */, 22},    { 0x4FB50AF /* up */, 0 } },
  { { RC5, 0xF90 /* Vol Up */, 24},    { 0x4FB50AF /* up */, 0 } },
  { { RC5, 0x791 /* Vol Down */, 22},  { 0x4FB8877 /* down */, 0 } },
  { { RC5, 0xF91 /* Vol Down */, 24},  { 0x4FB8877 /* down */, 0 } },
  { { RC5, 0x78D /* Menu(i) */, 22},   { 0x4FB9867 /* timer */, 0 } },
  { { RC5, 0xF8D /* Menu(i) */, 24},   { 0x4FB9867 /* timer */, 0 } },
//  { { RC5, 0x79F /* Back/Exit */, 24}, { ?          /* cancel timer */, 0 } },
//  { { RC5, 0xF9F /* Back/Exit */, 26}, { ?          /* cancel timer */, 0 } },
  { { RC5, 0x78E /* #/Sub/CC */, 22},         { 0x4FB00FF /* celsius/fahrenheit */, 0 } },
  { { RC5, 0xF8E /* #/Sub/CC */, 24},         { 0x4FB00FF /* celsius/fahrenheit */, 0 } },  
  
#endif

#if 1
  // LED lighting remote
  { { NEC, 0xFF2AD5, 68}, { 0x4FB40BF /* power */, 0 } },
  { { NEC, 0xFFAA55, 68}, { 0x4FB906F /* mode */, 0 } },
  { { NEC, 0xFF0AF5, 68}, { 0x4FB58A7 /* fan speed */, 0 } },
  { { NEC, 0xFF8A75, 68}, { 0x4FB50AF /* up */, 0 } },
  { { NEC, 0xFF38C7, 68}, { 0x4FB9867 /* timer */, 0 } },
  { { NEC, 0xFFB847, 68}, { 0x4FB8877 /* down */, 0 } },
//  { { NEC, 0xFF18E7, 68}, { ?          /* cancel timer */, 0 } },
  { { NEC, 0xFF9867, 68}, { 0x4FB00FF /* celsius/fahrenheit */, 0 } },  
#endif

  { { UNUSED, 0, 0}, {0} }
};

const int recvPin = 11;
const int blinkLEDPin = LED_BUILTIN;  // probably 13
IRrecv irrecv(recvPin);
IRsend irsend;

unsigned long lastTime = 0;
long lastValue = 0;
const xlat_entry *nextCode = NULL;

#define REPEAT_MILLIS 100
#define SILENCE_MILLIS 150

void dumpResults(decode_results &results) {
    Serial.print("decode_type: ");
    Serial.print(results.decode_type);
    Serial.print(" address: ");
    Serial.print(results.address, HEX);
    Serial.print(" value: ");
    Serial.print(results.value, HEX);
    Serial.print(" bits: ");
    Serial.print(results.bits);
    Serial.print(" overflow: ");
    Serial.print(results.overflow);
    Serial.print(" rawlen: ");
    Serial.print(results.rawlen);
    Serial.println("");
}

bool enable = false;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  Serial.println("Ready");
  lastTime = micros() - REPEAT_MILLIS;
  enable = false;
}

void loop() {
  decode_results results;
   
  results.address = 0;
  if (irrecv.decode(&results)) {
    unsigned long time = millis();
    
    // Simulate REPEAT
    if (lastValue == results.value && (signed long) (time - lastTime) < REPEAT_MILLIS) {
      results.value = REPEAT;
    } else {
      lastValue = results.value;
    }
    
    irrecv.resume();
    dumpResults(results);

    if (results.decode_type == NEC && results.rawlen == 68 && results.value == 0xFF50AF) {
      /* 'DIY6' button enables/disables translation. */
      enable = !enable;
      Serial.println(enable ? "Enabled" : "Disabled");
    } else if (enable) {
      for (const xlat_entry *e = xlat_table; e->in.decode_type != UNUSED; e++) {
        if (e->in.decode_type == results.decode_type &&
            e->in.value == results.value &&
            e->in.rawlen == results.rawlen)
        {
          // We can't send the code right away; we must wait until the
          // 38 kHz IR channel is idle before transmitting, to avoid
          // collisions.
          nextCode = e;
          Serial.println("Queued code");
          break;
        }
      }
    }
    
    lastTime = time = millis();

  } else if (nextCode != NULL) {
    unsigned long time = millis();
    if ((signed long) (time - lastTime) > SILENCE_MILLIS) {
      // Send the code
      irsend.sendNEC(nextCode->out.value, 32);

      // If idempotent, we can repeat the code for extra reliability.
      for (int i = 1; i < nextCode->out.repeat; i++) {
        delay(40);
        irsend.sendNEC(nextCode->out.value, 32);
      }

      Serial.print("Sent queued code: ");
      Serial.print(nextCode->out.value, HEX);
      Serial.println("");
      nextCode = 0;
      lastTime = time = millis();
  
      irrecv.enableIRIn();
      irrecv.resume();
    }
  }

  // Blink an LED
  pinMode(blinkLEDPin, OUTPUT);
  if (enable) {
    digitalWrite(blinkLEDPin, irrecv.isIdle() ? HIGH : LOW);
  } else {
    digitalWrite(blinkLEDPin, irrecv.isIdle() ? LOW : HIGH);
  }
}
