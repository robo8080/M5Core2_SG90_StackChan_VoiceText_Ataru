// Copyright (c) robo8080. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "AtaruEye.h"
namespace m5avatar {

AtaruEye::AtaruEye(uint16_t x, uint16_t y, uint16_t r, bool isLeft) : AtaruEye(r, isLeft) {}

AtaruEye::AtaruEye(uint16_t r, bool isLeft) : r{r}, isLeft{isLeft} {}
void AtaruEye::draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *ctx) {
  Expression exp = ctx->getExpression();
  uint32_t cx = rect.getCenterX();
  uint32_t cy = rect.getCenterY();
  Gaze g = ctx->getGaze();
  ColorPalette *cp = ctx->getColorPalette();
  uint16_t primaryColor = cp->get(COLOR_PRIMARY);
  uint16_t backgroundColor = COLOR_DEPTH == 1 ? ERACER_COLOR : cp->get(COLOR_BACKGROUND);
  uint32_t offsetX = g.getHorizontal() * 8;
  uint32_t offsetY = g.getVertical() * 5;
  float eor = ctx->getEyeOpenRatio();

  if (eor == 0) {
    // eye closed
    spi->fillRect(cx - 15, cy - 2, 30, 4, primaryColor);
    return;
  }
  if (exp == Expression::Happy) {
    spi->fillEllipse(cx, cy, 30, 25, primaryColor);
    spi->fillEllipse(cx, cy, 24, 19, backgroundColor);
    spi->fillRect(cx-30, cy, 60 ,27, backgroundColor);    
  } else {   
    spi->fillEllipse(cx, cy, 30, 25, primaryColor);
    spi->fillEllipse(cx, cy, 28, 23, backgroundColor);

    spi->fillEllipse(cx + offsetX, cy + offsetY, 18, 18,
                     primaryColor);
    spi->fillEllipse(cx + offsetX - 3, cy + offsetY - 3, 3, 3,
                     backgroundColor);

    if (exp == Expression::Sleepy) {
      spi->fillRect(cx-30, cy-27, 60 ,27, backgroundColor);
    }  
  }  
}

}  // namespace m5avatar
