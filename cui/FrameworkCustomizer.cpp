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
 * @file FrameworkCustomizer.cpp
 * @author Masahiro Tomono
 ****************************************************************************/

#include "FrameworkCustomizer.h"

using namespace std;

// フレームワークの基本部分を設定
void FrameworkCustomizer::makeFramework() {
  smat.setPoseEstimator(&poest);
  smat.setPoseFuser(&pfu);

  // LoopDetectorSSは使う部品が決まっているので、ここで入れる
  lpdSS.setPoseEstimator(&poest);
  lpdSS.setPoseFuser(&pfu);
  lpdSS.setDataAssociator(&dassGT);
  lpdSS.setCostFunction(&cfuncPD);
  lpdSS.setPointCloudMap(&pcmapLP);

  sfront->setScanMatcher(&smat);
}

/////// 実験用

// フレームワーク基本構成
void FrameworkCustomizer::customizeA() {
  pcmap = &pcmapBS;                                // 全スキャン点を保存する点群地図
  RefScanMaker *rsm = &rsmBS;                      // 直前スキャンを参照スキャンとする
  DataAssociator *dass = &dassLS;                  // 線形探索によるデータ対応づけ
  CostFunction *cfunc = &cfuncED;                  // ユークリッド距離をコスト関数とする
  PoseOptimizer *popt = &poptSD;                   // 最急降下法による最適化
  LoopDetector *lpd = &lpdDM;                      // ダミーのループ検出

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(false);                       // センサ融合しない
}

// 格子テーブルの利用
void FrameworkCustomizer::customizeB() {
  pcmap = &pcmapGT;                                // 格子テーブルで管理する点群地図
  RefScanMaker *rsm = &rsmLM;                      // 局所地図を参照スキャンとする
  DataAssociator *dass = &dassLS;                  // 線形探索によるデータ対応づけ
  CostFunction *cfunc = &cfuncED;                  // ユークリッド距離をコスト関数とする
  PoseOptimizer *popt = &poptSD;                   // 最急降下法による最適化
  LoopDetector *lpd = &lpdDM;                      // ダミーのループ検出

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(false);                       // センサ融合しない
}

// 最急降下法の後に直線探索を行う
void FrameworkCustomizer::customizeC() {
  pcmap = &pcmapGT;                                // 格子テーブルで管理する点群地図
  RefScanMaker *rsm = &rsmLM;                      // 局所地図を参照スキャンとする
  DataAssociator *dass = &dassLS;                  // 線形探索によるデータ対応づけ
  CostFunction *cfunc = &cfuncED;                  // ユークリッド距離をコスト関数とする
  PoseOptimizer *popt = &poptSL;                   // 最急降下法と直線探索による最適化
  LoopDetector *lpd = &lpdDM;                      // ダミーのループ検出

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(false);                       // センサ融合しない
}

// データ対応づけを格子テーブルで行う
void FrameworkCustomizer::customizeD() {
  pcmap = &pcmapGT;                                // 格子テーブルで管理する点群地図
  RefScanMaker *rsm = &rsmLM;                      // 局所地図を参照スキャンとする
  DataAssociator *dass = &dassGT;                  // 格子テーブルによるデータ対応づけ
  CostFunction *cfunc = &cfuncED;                  // ユークリッド距離をコスト関数とする
  PoseOptimizer *popt = &poptSL;                   // 最急降下法と直線探索による最適化
  LoopDetector *lpd = &lpdDM;                      // ダミーのループ検出

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(false);                       // センサ融合しない
}

// スキャン点間隔均一化を追加
void FrameworkCustomizer::customizeE() {
  pcmap = &pcmapGT;                                // 格子テーブルで管理する点群地図
  RefScanMaker *rsm = &rsmLM;                      // 局所地図を参照スキャンとする
  DataAssociator *dass = &dassGT;                  // 格子テーブルによるデータ対応づけ
  CostFunction *cfunc = &cfuncED;                  // ユークリッド距離をコスト関数とする
  PoseOptimizer *popt = &poptSL;                   // 最急降下法と直線探索による最適化
  LoopDetector *lpd = &lpdDM;                      // ダミーのループ検出

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  smat.setScanPointResampler(&spres);              // スキャン点間隔均一化
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(false);                       // センサ融合しない
}

// スキャン点の法線計算を追加
void FrameworkCustomizer::customizeF() {
  pcmap = &pcmapGT;                                // 格子テーブルで管理する点群地図
  RefScanMaker *rsm = &rsmLM;                      // 局所地図を参照スキャンとする
  DataAssociator *dass = &dassGT;                  // 格子テーブルによるデータ対応づけ
  CostFunction *cfunc = &cfuncPD;                  // 垂直距離をコスト関数とする
  PoseOptimizer *popt = &poptSL;                   // 最急降下法と直線探索による最適化
  LoopDetector *lpd = &lpdDM;                      // ダミーのループ検出

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  smat.setScanPointAnalyser(&spana);               // スキャン点の法線計算
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(false);                       // センサ融合しない
}

// スキャン点間隔均一化と法線計算を追加
void FrameworkCustomizer::customizeG() {
  pcmap = &pcmapGT;                                // 格子テーブルで管理する点群地図
  RefScanMaker *rsm = &rsmLM;                      // 局所地図を参照スキャンとする
  DataAssociator *dass = &dassGT;                  // 格子テーブルによるデータ対応づけ
  CostFunction *cfunc = &cfuncPD;                  // 垂直距離をコスト関数とする
  PoseOptimizer *popt = &poptSL;                   // 最急降下法と直線探索による最適化
  LoopDetector *lpd = &lpdDM;                      // ダミーのループ検出

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  smat.setScanPointResampler(&spres);              // スキャン点間隔均一化
  smat.setScanPointAnalyser(&spana);               // スキャン点の法線計算
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(false);                       // センサ融合しない
}

// センサ融合を追加
void FrameworkCustomizer::customizeH() {
//  pcmap = &pcmapGT;                                // 格子テーブルで管理する点群地図
  pcmap = &pcmapLP;                                // 部分地図ごとに管理する点群地図。cIとの比較用
  RefScanMaker *rsm = &rsmLM;                      // 局所地図を参照スキャンとする
  DataAssociator *dass = &dassGT;                  // 格子テーブルによるデータ対応づけ
  CostFunction *cfunc = &cfuncPD;                  // 垂直距離をコスト関数とする
  PoseOptimizer *popt = &poptSL;                   // 最急降下法と直線探索による最適化
  LoopDetector *lpd = &lpdDM;                      // ダミーのループ検出

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  smat.setScanPointResampler(&spres);
  smat.setScanPointAnalyser(&spana);
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(true);                        // センサ融合する
//  sfront->setDgCheck(false);                        // センサ融合しない
}

// センサ融合とループ閉じ込みを追加
void FrameworkCustomizer::customizeI() {
  pcmap = &pcmapLP;                                // 部分地図ごとに管理する点群地図
  RefScanMaker *rsm = &rsmLM;                      // 局所地図を参照スキャンとする
  DataAssociator *dass = &dassGT;                  // 格子テーブルによるデータ対応づけ
  CostFunction *cfunc = &cfuncPD;                  // 垂直距離をコスト関数とする
  PoseOptimizer *popt = &poptSL;                   // 最急降下法と直線探索による最適化
  LoopDetector *lpd = &lpdSS;                      // 部分地図を用いたループ検出

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  smat.setScanPointResampler(&spres);
  smat.setScanPointAnalyser(&spana);
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(true);                        // センサ融合する
}

// ガウスニュートン法
void FrameworkCustomizer::customizeJ() {
  pcmap = &pcmapLP;                                // 部分地図ごとに管理する点群地図
  RefScanMaker *rsm = &rsmLM;                      // 局所地図を参照スキャンとする
  DataAssociator *dass = &dassGT;                  // 格子テーブルによるデータ対応づけ
  CostFunction *cfunc = &cfuncPD;                  // 垂直距離をコスト関数とする
  PoseOptimizer *popt = &poptGN;                   // ガウスニュートン法による最適化
  LoopDetector *lpd = &lpdSS;                      // 部分地図を用いたループ検出

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);
  smat.setPointCloudMap(pcmap);
  smat.setRefScanMaker(rsm);
  smat.setScanPointResampler(&spres);
  smat.setScanPointAnalyser(&spana);
  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setDgCheck(true);                        // センサ融合する
}

// ロバストコスト関数。退化処理なし。ループ閉じ込みなし。
void FrameworkCustomizer::customizeK() {
  pcmap = &pcmapLP;                                // 部分地図ごとに管理する点群地図
  RefScanMaker *rsm = &rsmLM;                      // 局所地図を参照スキャンとする
  DataAssociator *dass = &dassGT;                  // 最近傍探索によるデータ対応づけ
  CostFunction *cfunc = &cfuncPD;                  // 垂直距離をコスト関数とする
  PoseOptimizer *popt = &poptGN;                   // ガウスニュートン法による最適化
  LoopDetector *lpd = &lpdDM;                      // ダミーのループ検出

//  dass->setDthre(2.0);
  poptGN.setHasOutliers(true);                     // 外れ値を生成する
  poptGN.setBeRobust(true);                        // ロバストコスト関数

  popt->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt);
  pfu.setDataAssociator(dass);

  smat2.setPointCloudMap(pcmap);
  smat2.setRefScanMaker(rsm);
  smat2.setScanPointResampler(&spres);
  smat2.setScanPointAnalyser(&spana);
  smat2.setPoseEstimator(&poest);
  smat2.setPoseFuser(&pfu);

  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setScanMatcher(&smat2);
}

// MAP推定
void FrameworkCustomizer::customizeL() {
  pcmap = &pcmapLP;                                // 部分地図ごとに管理する点群地図
  poptMAP.setPointCloudMap(pcmap);

  RefScanMaker *rsm = &rsmLM;                      // 局所地図を参照スキャンとする
  DataAssociator *dass = &dassGT;                  // 最近傍探索によるデータ対応づけ
  CostFunction *cfunc = &cfuncPD;                  // 垂直距離をコスト関数とする
  PoseOptimizer *popt1 = &poptMAP;                 // 逐次SLAM用。MAP推定あり
  PoseOptimizer *popt2 = &poptGN;                  // ループ閉じ込み用。MAP推定なし
  LoopDetector *lpd = &lpdSS;                      // 部分地図を用いたループ検出  
  lpdSS.setPoseEstimator(&poest2);

  popt1->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt1);

  popt2->setCostFunction(cfunc);
  poest2.setDataAssociator(dass);
  poest2.setPoseOptimizer(popt2);
  pfu.setDataAssociator(dass);
  
  smat2.setPoseEstimator(&poest);
  smat2.setPoseFuser(&pfu);
  smat2.setPointCloudMap(pcmap);
  smat2.setRefScanMaker(rsm);
  smat2.setScanPointResampler(&spres);
  smat2.setScanPointAnalyser(&spana);

  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setScanMatcher(&smat2);
}

// kd木
void FrameworkCustomizer::customizeM() {
  pcmap = &pcmapLP;                                // 部分地図ごとに管理する点群地図
  poptMAP.setPointCloudMap(pcmap);

  RefScanMaker *rsm = &rsmLM;                      // 局所地図を参照スキャンとする
//  DataAssociator *dass = &dassLS;                  // 最近傍探索によるデータ対応づけ
//  DataAssociator *dass = &dassGT;                  // 最近傍探索によるデータ対応づけ
  DataAssociator *dass = &dassNN;                  // 最近傍探索によるデータ対応づけ
  CostFunction *cfunc = &cfuncPD;                  // 垂直距離をコスト関数とする
  PoseOptimizer *popt1 = &poptMAP;                 // 逐次SLAM用。MAP推定あり
  PoseOptimizer *popt2 = &poptGN;                  // ループ閉じ込み用。MAP推定なし
  LoopDetector *lpd = &lpdSS;                      // 部分地図を用いたループ検出  
  lpdSS.setPoseEstimator(&poest2);

//  dass->setDthre(2.0);
//  poptMAP.setHasOutliers(true);                    // 外れ値を生成する
//  poptMAP.setBeRobust(true);                       // dassのdthreが大きいときはtrueにした方がよい
//  poptGN.setBeRobust(true);                        // dassのdthreが大きいときはtrueにした方がよい

  popt1->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt1);

  popt2->setCostFunction(cfunc);
  poest2.setDataAssociator(dass);
  poest2.setPoseOptimizer(popt2);
  pfu.setDataAssociator(dass);
  
  smat2.setPoseEstimator(&poest);
  smat2.setPoseFuser(&pfu);
  smat2.setPointCloudMap(pcmap);
  smat2.setRefScanMaker(rsm);
  smat2.setScanPointResampler(&spres);
  smat2.setScanPointAnalyser(&spana);

  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setScanMatcher(&smat2);
}

// ロバストポーズ調整
void FrameworkCustomizer::customizeN() {
  pcmap = &pcmapLP;                                // 部分地図ごとに管理する点群地図
  poptMAP.setPointCloudMap(pcmap);

  RefScanMaker *rsm = &rsmLM;                      // 局所地図を参照スキャンとする
  DataAssociator *dass = &dassNN;                  // 最近傍探索によるデータ対応づけ
  CostFunction *cfunc = &cfuncPD;                  // 垂直距離をコスト関数とする
  PoseOptimizer *popt1 = &poptMAP;                 // 逐次SLAM用。MAP推定あり
  PoseOptimizer *popt2 = &poptGN;                  // ループ閉じ込み用。MAP推定なし
  LoopDetector *lpd = &lpdSS;                      // 部分地図を用いたループ検出  
  lpdSS.setPoseEstimator(&poest2);

  dass->setDthre(2.0);
//  poptMAP.setHasOutliers(true);                    // 外れ値を生成する
  poptMAP.setBeRobust(true);                       // ロバストコスト関数
//  poptGN.setHasOutliers(true);                     // ロバストコスト関数
  poptGN.setBeRobust(true);                        // ロバストコスト関数

  popt1->setCostFunction(cfunc);
  poest.setDataAssociator(dass);
  poest.setPoseOptimizer(popt1);

  popt2->setCostFunction(cfunc);
  poest2.setDataAssociator(dass);
  poest2.setPoseOptimizer(popt2);
  pfu.setDataAssociator(dass);
  
  smat2.setPoseEstimator(&poest);
  smat2.setPoseFuser(&pfu);
  smat2.setPointCloudMap(pcmap);
  smat2.setRefScanMaker(rsm);
  smat2.setScanPointResampler(&spres);
  smat2.setScanPointAnalyser(&spana);

  sfront->setLoopDetector(lpd);
  sfront->setPointCloudMap(pcmap);
  sfront->setScanMatcher(&smat2);
  
  SlamBackEnd *sback = sfront->getSlamBackend();
  sback->setHasOutliers(true);
  sback->setBeRobust(true);
}
