// Copyright (c) robo8080 All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "RamEye.h"
namespace m5avatar {

RamEye::RamEye(uint16_t x, uint16_t y, uint16_t r, bool isLeft) : RamEye(r, isLeft) {}

RamEye::RamEye(uint16_t r, bool isLeft) : r{r}, isLeft{isLeft} {}
void RamEye::draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *ctx) {
  Expression exp = ctx->getExpression();
  uint32_t x = rect.getCenterX();
  uint32_t y = rect.getCenterY();
  Gaze g = ctx->getGaze();
  float openRatio = ctx->getEyeOpenRatio();
  uint32_t offsetX = g.getHorizontal() * 5;
  uint32_t offsetY = g.getVertical() * 7;
  uint16_t primaryColor = ctx->getColorPalette()->get(COLOR_PRIMARY);
  uint16_t backgroundColor = ctx->getColorPalette()->get(COLOR_BACKGROUND);
  if (openRatio > 0) {
    if (exp == Expression::Neutral || exp == Expression::Doubt || exp == Expression::Angry) {
      if(isLeft) {
        spi->fillEllipse(x+13 , y-25 , 18, 10, primaryColor);
        spi->fillEllipse(x+13 , y-8-25 , 18, 10, backgroundColor);
      }else {
        spi->fillEllipse(x-13 , y-25 , 18, 10, primaryColor);
        spi->fillEllipse(x-13 , y-8-25 , 18, 10, backgroundColor);
      }
    }
    spi->fillEllipse(x , y , r, r + 5, primaryColor);
    spi->fillCircle(x + offsetX, y + offsetY, 10, backgroundColor);
    // TODO(meganetaaan): Refactor
    if (exp == Expression::Angry || exp == Expression::Sad) {
      int x0, y0, x1, y1, x2, y2;
      x0 = x - r;
      y0 = y - r - 5;
      x1 = x0 + r * 2;
      y1 = y0;
      x2 = !isLeft != !(exp == Expression::Sad) ? x0 : x1;
      y2 = y0 + r;
      spi->fillTriangle(x0, y0, x1, y1, x2, y2, backgroundColor);
    } else if (exp == Expression::Happy || exp == Expression::Sleepy) {
      int x0, y0, w, h;
      x0 = x - r;
      y0 = y - r -5;
      w = r * 2 + 4;
      h = r + 7;
      if (exp == Expression::Happy) {
        y0 += (r + 5);
        spi->fillEllipse(x , y , r / 1.5, (r + 5) / 1.5, backgroundColor);
      }
      spi->fillRect(x0, y0, w, h, backgroundColor);
    }
  } else {
    int x1 = x - r + offsetX;
    int y1 = y - 2 + offsetY;
    int w = r * 2;
    int h = 4;
    spi->fillRect(x1, y1, w, h, primaryColor);
  }
}
}  // namespace m5avatar
