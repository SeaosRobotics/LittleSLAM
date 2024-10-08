﻿/****************************************************************************
 * LittleSLAM: 2D-Laser SLAM for educational use
 * Copyright (C) 2017-2018 Masahiro Tomono
 * Copyright (C) 2018 Future Robotics Technology Center (fuRo),
 *                    Chiba Institute of Technology.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * @file DataAssociator.h
 * @author Masahiro Tomono
 ****************************************************************************/

#ifndef DATA_ASSOCIATOR_H_
#define DATA_ASSOCIATOR_H_

#include <vector>
#include "MyUtil.h"
#include "LPoint2D.h"
#include "Pose2D.h"
#include "Scan2D.h"

class DataAssociator
{
protected:
  double dthre;                                // これ以上遠い点は対象外
  double totalTime;                            // 調査用
  int timeCnt;                                 // 調査用

public:
  std::vector<const LPoint2D*> curLps;            // 対応がとれた現在スキャンの点群
  std::vector<const LPoint2D*> refLps;            // 対応がとれた参照スキャンの点群

  DataAssociator() : dthre(0.2), totalTime(0), timeCnt(0) {
  }

  ~DataAssociator() {
  }

  void setDthre(double d) {
    dthre = d;
  }

  void averageProcTime() {
    double avg = totalTime/timeCnt;
    printf("DataAssociator: average processing time=%g\n", avg);
  }

  virtual void setRefBase(const std::vector<LPoint2D> &lps) = 0;
  virtual double findCorrespondence(const Scan2D *curScan, const Pose2D &predPose) = 0;
};

#endif
