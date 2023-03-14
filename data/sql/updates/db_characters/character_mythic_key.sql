/*
 Navicat Premium Data Transfer

 Source Server         : Valanior
 Source Server Type    : MySQL
 Source Server Version : 80032
 Source Host           : 151.80.58.21:3306
 Source Schema         : acore_characters

 Target Server Type    : MySQL
 Target Server Version : 80032
 File Encoding         : 65001

 Date: 11/03/2023 17:14:00
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for character_mythic_key
-- ----------------------------
DROP TABLE IF EXISTS `character_mythic_key`;
CREATE TABLE `character_mythic_key`  (
  `guid` int(0) NOT NULL,
  `mapId` int(0) NULL DEFAULT NULL,
  `level` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `createdAt` datetime(0) NULL DEFAULT NULL,
  PRIMARY KEY (`guid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
