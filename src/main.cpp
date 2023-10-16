// Copyright (c) 2023 Inaba (@hollyhockberry)
// This software is released under the MIT License.
// http://opensource.org/licenses/mit-license.php

#include <M5Unified.h>
#include <Avatar.h>

using namespace m5avatar;

namespace {
Face face(new Mouth(50, 90, 4, 60), new BoundingRect(160, 163-40),
          new Eye(8, false), new BoundingRect(93, 90-35),
          new Eye(8, true), new BoundingRect(96, 230-40),
          new Eyeblow(32, 0, false), new BoundingRect(67, 96-35),
          new Eyeblow(32, 0, true), new BoundingRect(72, 230-40));
Avatar avatar(&face);
} // namespace

void setup() {
  M5.begin();
  M5.Display.setRotation(180);
  avatar.init();
}

void loop() {
  M5.update();
  if (M5.BtnA.wasClicked()) {
    avatar.setExpression((Expression)(random() % 6));
  }
  auto f = random(90) / 100.f;
  avatar.setMouthOpenRatio(f);
}
