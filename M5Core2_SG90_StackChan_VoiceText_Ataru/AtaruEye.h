// Copyright (c) robo8080. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef ATARUEYE_H_
#define ATARUEYE_H_

#include <utility/In_eSPI.h>
#include "DrawContext.h"
#include "Drawable.h"

namespace m5avatar {

class AtaruEye final : public Drawable {
 private:
  uint16_t r;
  bool isLeft;

 public:
  // constructor
  AtaruEye() = delete;
  AtaruEye(uint16_t x, uint16_t y, uint16_t r, bool isLeft);  // deprecated
  AtaruEye(uint16_t r, bool isLeft);
  ~AtaruEye() = default;
  AtaruEye(const AtaruEye &other) = default;
  AtaruEye &operator=(const AtaruEye &other) = default;
  void draw(TFT_eSPI *spi, BoundingRect rect,
            DrawContext *drawContext) override;
  // void draw(TFT_eSPI *spi, DrawContext *drawContext) override; // deprecated
};

}  // namespace m5avatar

#endif  // ATARUEYE_H_
