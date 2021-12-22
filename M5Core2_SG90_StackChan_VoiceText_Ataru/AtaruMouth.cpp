// Copyright (c) robo8080. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "AtaruMouth.h"

namespace m5avatar {

AtaruMouth::AtaruMouth(uint16_t minWidth, uint16_t maxWidth, uint16_t minHeight,
             uint16_t maxHeight)
    : minWidth{minWidth},
      maxWidth{maxWidth},
      minHeight{minHeight},
      maxHeight{maxHeight} {}

void AtaruMouth::draw(TFT_eSPI *spi, BoundingRect rect, DrawContext *ctx) {
  Expression exp = ctx->getExpression();
  uint16_t primaryColor = ctx->getColorPalette()->get(COLOR_PRIMARY);
  uint16_t backgroundColor = ctx->getColorPalette()->get(COLOR_BACKGROUND);
  float breath = _min(1.0f, ctx->getBreath());
  float openRatio = ctx->getMouthOpenRatio();
  Gaze g = ctx->getGaze();                    //
  uint32_t offsetY = g.getVertical() * 10;    //
  int h = minHeight + (maxHeight - minHeight) * openRatio;
  int w = minWidth + (maxWidth - minWidth) * (1 - openRatio);
  int x = rect.getLeft() - w / 2;
  int y = rect.getTop() - h / 2 + breath * 2;
  if (openRatio == 0.0)
  {
    if (exp == Expression::Neutral || exp == Expression::Happy) {
      spi->fillEllipse(x+w/2, y+h/2, w/2, minHeight*6+offsetY, primaryColor);       //+offsetY
      spi->fillEllipse(x+w/2, y+h/2-5, w/2, minHeight*6+offsetY, backgroundColor);  //+offsetY
      spi->fillRect(x, y+h/2- minHeight*6-5, w, minHeight*6+5, backgroundColor);
    }else if (exp == Expression::Angry || exp == Expression::Sad) {
        spi->fillEllipse(x+w/2, y+h/2+minHeight*6, w/2, minHeight*6, primaryColor);
        spi->fillEllipse(x+w/2, y+h/2+5+minHeight*6, w/2, minHeight*6, backgroundColor);
        spi->fillRect(x, y+h/2+ minHeight*6, w, minHeight*6+5, backgroundColor);    
    } else {
      spi->fillRect(x, y, w, h, primaryColor);
    }
  } else {
    spi->fillEllipse(x+w/2, y+h/2, w/2, h/2, primaryColor);
    spi->fillEllipse(x+w/2, y+h/2, w/2-3, h/2-3, TFT_RED);
  }
  int h1 = minHeight;
  int w1 = maxWidth;
  int x1 = rect.getLeft() - w1 / 2;
  int y1 = rect.getTop() - h1 / 2 + breath * 2;
  spi->fillCircle(x1 - 30, y1 , 25, TFT_PINK);
  spi->fillCircle(x1 + w1 + 30, y1 , 25, TFT_PINK);

  
}

}  // namespace m5avatar
