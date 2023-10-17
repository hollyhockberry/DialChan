// Copyright (c) 2023 Inaba (@hollyhockberry)
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php

#include <M5Unified.h>
#include <Avatar.h>
#include <driver/pcnt.h>

using namespace m5avatar;

namespace {
Face face(new Mouth(50, 90, 4, 60), new BoundingRect(160, 163-40),
          new Eye(8, false), new BoundingRect(93, 90-35),
          new Eye(8, true), new BoundingRect(96, 230-40),
          new Eyeblow(32, 0, false), new BoundingRect(67, 96-35),
          new Eyeblow(32, 0, true), new BoundingRect(72, 230-40));
Avatar avatar(&face);

void init_pcnt() {
  pcnt_config_t cfg = {
    .pulse_gpio_num = 40,
    .ctrl_gpio_num = 41,
    .lctrl_mode = PCNT_MODE_KEEP,
    .hctrl_mode = PCNT_MODE_REVERSE,
    .pos_mode = PCNT_COUNT_INC,
    .neg_mode = PCNT_COUNT_DEC,
    .counter_h_lim = 32767,
    .counter_l_lim = -32768,
    .unit = PCNT_UNIT_0,
    .channel = PCNT_CHANNEL_0
  };

  ::pcnt_unit_config(&cfg);
  ::pcnt_counter_pause(PCNT_UNIT_0);
  ::pcnt_counter_clear(PCNT_UNIT_0);
  ::pcnt_counter_resume(PCNT_UNIT_0);  
}

int16_t get_pcnt() {
  int16_t count = 0;
  ::pcnt_get_counter_value(PCNT_UNIT_0, &count);
  return count;
}

template<typename T, std::size_t SIZE>
std::size_t array_length(const T (&)[SIZE]) {   
    return SIZE;
}
 
uint16_t colors[] = { WHITE, RED, BLUE, GREEN, YELLOW, };
int current_color = 0;

} // namespace

void setup() {
  M5.begin();
  M5.Display.setRotation(2);
  avatar.init();

  init_pcnt();
}

void loop() {
  M5.update();
  if (M5.BtnA.wasClicked()) {
    avatar.setExpression((Expression)(random() % 6));
  }
  const auto color = get_pcnt() % array_length(colors);

  if (current_color != color) {
    auto cp = avatar.getColorPalette();
    cp.set(COLOR_PRIMARY, colors[color]);
    avatar.setColorPalette(cp);
    current_color = color;
  }
  auto f = random(90) / 100.f;
  avatar.setMouthOpenRatio(f);
}
