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
 * @file DataAssociatorGT.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "DataAssociatorGT.h"

using namespace std;


// 現在スキャンcurScanの各スキャン点をpredPoseで座標変換した位置に最も近い点を見つける
double DataAssociatorGT::findCorrespondence(const Scan2D *curScan, const Pose2D &predPose) {
  chrono_time t0 = clock();  

  curLps.clear();                                   // 対応づけ現在スキャン点群を空にする
  refLps.clear();                                   // 対応づけ参照スキャン点群を空にする

  nntab.setDthre(dthre);

  for (size_t i=0; i<curScan->lps.size(); i++) {
    const LPoint2D *clp = &(curScan->lps[i]);       // 現在スキャンの点。ポインタで。

    // 格子テーブルにより最近傍点を求める。格子テーブル内に距離閾値dthreがあることに注意。
    const LPoint2D *rlp = nntab.findClosestPoint(clp, predPose);
 
    if (rlp != nullptr) {
      curLps.push_back(clp);                        // 最近傍点があれば登録
      refLps.push_back(rlp);
    }
  }

  double ratio = (1.0*curLps.size())/curScan->lps.size();         // 対応がとれた点の比率

  chrono_time t1 = clock();  
  totalTime += duration(t0, t1);                // 処理時間
  ++timeCnt;

  return(ratio);
}
