// Copyright (c) robo8080. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#ifndef FACES_RAMFACE_H_
#define FACES_RAMFACE_H_

# if defined(ARDUINO_M5STACK_Core2) || defined(M5AVATAR_CORE2) || defined(_M5Core2_H_)
  #include <M5Core2.h>
# else
  #include <M5Stack.h> // TODO(meganetaaan): include only the Sprite function not a whole library
# endif
#include "RamEye.h"
#include "RamMouth.h"
#include "RamEyeblow.h"

namespace m5avatar {
class RamFace : public Face {
 public:
  RamFace()
      : Face(new RamMouth(50, 100, 4, 60), new BoundingRect(150, 163), 
             new RamEye(23, false), new BoundingRect(93, 90),
             new RamEye(23, true),  new BoundingRect(93, 230),
             new RamEyeblow(20, 3, false), new BoundingRect(55, 90),
             new RamEyeblow(20, 3, true),  new BoundingRect(55, 230)) {}
};

}  // namespace m5avatar

#endif  // FACES_RAMFACE_H_
