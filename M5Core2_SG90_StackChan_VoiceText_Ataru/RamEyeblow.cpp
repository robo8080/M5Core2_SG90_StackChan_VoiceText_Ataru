// Copyright (c) robo8080 All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "RamEyeblow.h"
namespace m5avatar {

RamEyeblow::RamEyeblow(uint16_t w, uint16_t h, bool isLeft)
    : width{w}, height{h}, isLeft{isLeft} {}

void RamEyeblow::draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *ctx) {
  Expression exp = ctx->getExpression();
  uint32_t x = rect.getLeft();
  uint32_t y = rect.getTop();
  Gaze g = ctx->getGaze();
  uint32_t offsetX = g.getHorizontal() * 5;
  uint32_t offsetY = g.getVertical() * 7;
  x += offsetX;
  y += offsetY;
  uint32_t primaryColor = ctx->getColorPalette()->get(COLOR_PRIMARY);
  if (width == 0 || height == 0) {
    return;
  }
  // draw two triangles to make rectangle
  if (exp == Expression::Angry || exp == Expression::Sad) {
    int x1, y1, x2, y2, x3, y3, x4, y4;
    int a = isLeft ^ (exp == Expression::Sad) ? -1 : 1;
    int dx = a * 3;
    int dy = a * 5;
    x1 = x - width / 2;
    x2 = x1 - dx;
    x4 = x + width / 2;
    x3 = x4 + dx;
    y1 = y - height / 2 - dy;
    y2 = y + height / 2 - dy;
    y3 = y - height / 2 + dy;
    y4 = y + height / 2 + dy;
    spi->fillTriangle(x1, y1, x2, y2, x3, y3, (uint16_t)primaryColor);
    spi->fillTriangle(x2, y2, x3, y3, x4, y4, (uint16_t)primaryColor);
  } else if(exp == Expression::Doubt || exp == Expression::Neutral || exp == Expression::Sleepy) {
    if (exp == Expression::Sleepy) {
      y = y + 20;
    }
    int x1 = x - width / 2;
    int y1 = y - height / 2;
    spi->fillRect(x1, y1, width, height, (uint16_t)primaryColor);
  } else {
    if (exp == Expression::Happy) {
        y = y - 5;
    }
    int x1, y1, x2, y2, x3, y3, x4, y4;
    int a = isLeft ^ (exp == Expression::Happy) ? -1 : 1;
    int dx = a * 1;
    int dy = a * 2;
    x1 = x - width / 2;
    x2 = x1 - dx;
    x4 = x + width / 2;
    x3 = x4 + dx;
    y1 = y - height / 2 - dy;
    y2 = y + height / 2 - dy;
    y3 = y - height / 2 + dy;
    y4 = y + height / 2 + dy;
    spi->fillTriangle(x1, y1, x2, y2, x3, y3, (uint16_t)primaryColor);
    spi->fillTriangle(x2, y2, x3, y3, x4, y4, (uint16_t)primaryColor);
  }
}

}  // namespace m5avatar
