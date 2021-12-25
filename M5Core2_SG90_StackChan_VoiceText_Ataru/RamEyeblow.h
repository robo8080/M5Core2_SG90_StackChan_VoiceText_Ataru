// Copyright (c) robo8080 All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef RAMEYEBLOW_H_
#define RAMEYEBLOW_H_

#include <utility/In_eSPI.h>
#include "BoundingRect.h"
#include "DrawContext.h"
#include "Drawable.h"

namespace m5avatar {
class RamEyeblow final : public Drawable {
 private:
  uint16_t width;
  uint16_t height;
  bool isLeft;

 public:
  // constructor
  RamEyeblow() = delete;
  RamEyeblow(uint16_t w, uint16_t h, bool isLeft);
  ~RamEyeblow() = default;
  RamEyeblow(const RamEyeblow &other) = default;
  RamEyeblow &operator=(const RamEyeblow &other) = default;
  void draw(TFT_eSPI *spi, BoundingRect rect,
            DrawContext *drawContext) override;
};

}  // namespace m5avatar

#endif  // RAMEYEBLOW_H_
