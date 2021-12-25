// Copyright (c) robo8080 All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef RAMEYE_H_
#define RAMEYE_H_

#include <utility/In_eSPI.h>
#include "DrawContext.h"
#include "Drawable.h"

namespace m5avatar {

class RamEye final : public Drawable {
 private:
  uint16_t r;
  bool isLeft;

 public:
  // constructor
  RamEye() = delete;
  RamEye(uint16_t x, uint16_t y, uint16_t r, bool isLeft);  // deprecated
  RamEye(uint16_t r, bool isLeft);
  ~RamEye() = default;
  RamEye(const RamEye &other) = default;
  RamEye &operator=(const RamEye &other) = default;
  void draw(TFT_eSPI *spi, BoundingRect rect,
            DrawContext *drawContext) override;
  // void draw(TFT_eSPI *spi, DrawContext *drawContext) override; // deprecated
};

}  // namespace m5avatar

#endif  // RAMEYE_H_
