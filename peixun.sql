/*
 Navicat Premium Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 80033
 Source Host           : localhost:3306
 Source Schema         : peixun

 Target Server Type    : MySQL
 Target Server Version : 80033
 File Encoding         : 65001

 Date: 06/07/2023 01:30:01
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for programmer
-- ----------------------------
DROP TABLE IF EXISTS `programmer`;
CREATE TABLE `programmer`  (
  `id` int(0) NOT NULL AUTO_INCREMENT,
  `name` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `sex` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `age` int(0) NULL DEFAULT NULL,
  `gongling` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`id`, `gongling`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of programmer
-- ----------------------------
INSERT INTO `programmer` VALUES (1, '夏登民', '1', 23, '1');
INSERT INTO `programmer` VALUES (2, '夏夏', '1', 24, '2');
INSERT INTO `programmer` VALUES (3, '登', '0', 25, '3');
INSERT INTO `programmer` VALUES (4, '张三', '1', 26, '4');
INSERT INTO `programmer` VALUES (5, '李四', '1', 27, '5');
INSERT INTO `programmer` VALUES (6, '王五', '1', 28, '6');
INSERT INTO `programmer` VALUES (7, '夏登民', '1', 29, '7');
INSERT INTO `programmer` VALUES (8, '夏夏', '1', 30, '8');
INSERT INTO `programmer` VALUES (9, '登', '0', 31, '9');
INSERT INTO `programmer` VALUES (10, '张三', '1', 32, '10');
INSERT INTO `programmer` VALUES (11, '李四', '1', 33, '11');
INSERT INTO `programmer` VALUES (12, '王五', '1', 34, '12');
INSERT INTO `programmer` VALUES (13, '夏登民', '1', 35, '13');
INSERT INTO `programmer` VALUES (14, '夏夏', '1', 36, '14');
INSERT INTO `programmer` VALUES (15, '登', '0', 37, '15');
INSERT INTO `programmer` VALUES (16, '张三', '1', 38, '16');
INSERT INTO `programmer` VALUES (17, '李四', '1', 39, '17');
INSERT INTO `programmer` VALUES (18, '王五', '1', 40, '18');

-- ----------------------------
-- Table structure for student
-- ----------------------------
DROP TABLE IF EXISTS `student`;
CREATE TABLE `student`  (
  `id` int(0) NOT NULL AUTO_INCREMENT,
  `name` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `sex` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `age` int(0) NULL DEFAULT NULL,
  `xuehao` varchar(32) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `major` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`, `xuehao`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of student
-- ----------------------------
INSERT INTO `student` VALUES (1, '夏登民', '1', 23, '2019031108', '土木工程');
INSERT INTO `student` VALUES (2, '夏夏', '1', 24, '2019031109', '计算机科学与技术');
INSERT INTO `student` VALUES (3, '登', '0', 25, '2019031110', '软件工程');
INSERT INTO `student` VALUES (4, '张三', '1', 26, '2019031111', '机械工程');
INSERT INTO `student` VALUES (5, '李四', '1', 27, '2019031112', '信息工程');
INSERT INTO `student` VALUES (6, '王五', '1', 28, '2019031113', '电子信息');
INSERT INTO `student` VALUES (7, '夏登民', '1', 23, '2019031114', '土木工程');
INSERT INTO `student` VALUES (8, '夏夏', '1', 24, '2019031115', '计算机科学与技术');
INSERT INTO `student` VALUES (9, '登', '0', 25, '2019031116', '软件工程');
INSERT INTO `student` VALUES (10, '张三', '1', 26, '2019031117', '机械工程');
INSERT INTO `student` VALUES (11, '李四', '1', 27, '2019031118', '信息工程');
INSERT INTO `student` VALUES (12, '王五', '1', 28, '2019031119', '电子信息');
INSERT INTO `student` VALUES (13, '夏登民', '1', 23, '2019031120', '土木工程');
INSERT INTO `student` VALUES (14, '夏夏', '1', 24, '2019031121', '计算机科学与技术');
INSERT INTO `student` VALUES (15, '登', '0', 25, '2019031122', '软件工程');
INSERT INTO `student` VALUES (16, '张三', '1', 26, '2019031123', '机械工程');
INSERT INTO `student` VALUES (17, '李四', '1', 27, '2019031124', '信息工程');
INSERT INTO `student` VALUES (18, '王五', '1', 28, '2019031125', '电子信息');

SET FOREIGN_KEY_CHECKS = 1;
