// Copyright (c) robo8080. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef ATARUMOUTH_H_
#define ATARUMOUTH_H_

#include <utility/In_eSPI.h>
#include "BoundingRect.h"
#include "DrawContext.h"
#include "Drawable.h"

namespace m5avatar {
class AtaruMouth final : public Drawable {
 private:
  uint16_t minWidth;
  uint16_t maxWidth;
  uint16_t minHeight;
  uint16_t maxHeight;

 public:
  // constructor
  AtaruMouth() = delete;
  ~AtaruMouth() = default;
  AtaruMouth(const AtaruMouth &other) = default;
  AtaruMouth &operator=(const AtaruMouth &other) = default;
  AtaruMouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight,
        uint16_t maxHeight);
  void draw(TFT_eSPI *spi, BoundingRect rect,
            DrawContext *drawContext) override;
};

}  // namespace m5avatar

#endif  // ATARUMOUTH_H_
