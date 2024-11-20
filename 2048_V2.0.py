import pygame
import random
import pygetwindow as gw
import pyautogui
import keyboard
import copy
import math
import numpy as np

# 游戏界面大小
GRID_SIZE = 4
CELL_SIZE = 100
GRID_WIDTH = GRID_SIZE * CELL_SIZE
GRID_HEIGHT = GRID_SIZE * CELL_SIZE

# 颜色定义
BACKGROUND_COLOR = (187, 173, 160)
CELL_COLOR = (205, 193, 180)
TEXT_COLOR = (255, 255, 255)


def draw_text(value, rect):
  # 绘制方块中的数字
  text_surface = font.render(str(value), True, TEXT_COLOR)
  text_rect = text_surface.get_rect()
  text_rect.center = rect.center
  window.blit(text_surface, text_rect)


def get_cell_color(value):
  # 根据方块的值获取对应的颜色
  colors = {
      0: (205, 193, 180),
      2: (238, 228, 218),
      4: (237, 224, 200),
      8: (242, 177, 121),
      16: (245, 149, 99),
      32: (246, 124, 95),
      64: (246, 94, 59),
      128: (237, 207, 114),
      256: (237, 204, 97),
      512: (237, 200, 80),
      1024: (237, 197, 63),
      2048: (237, 194, 46),
  }
  return colors.get(value, (0, 0, 0))


def add_new_tile():
  # 在随机空位置生成一个新数字（2或4）
  empty_cells = [(i, j) for i in range(GRID_SIZE) for j in range(GRID_SIZE) if grid[i][j] == 0]
  if empty_cells:
    row, col = random.choice(empty_cells)
    grid[row][col] = random.choice([2, 4])


def move_tiles_left(self):
  # 向左移动所有数字块
  move = False
  temp_score = 0
  for row in range(GRID_SIZE):
    merged = [False] * GRID_SIZE
    for col in range(1, GRID_SIZE):
      if self[row][col] != 0:
        k = col
        while k > 0 and self[row][k - 1] == 0:
          move = True
          self[row][k - 1] = self[row][k]
          self[row][k] = 0
          k -= 1
        if k > 0 and not merged[k - 1] and self[row][k - 1] == self[row][k]:
          move = True
          self[row][k - 1] *= 2
          self[row][k] = 0
          merged[k - 1] = True
          temp_score += self[row][k - 1]  # 更新积分
  return move, temp_score


def move_tiles_up(self):
  # 向上移动所有数字块
  move = False
  temp_score = 0
  for col in range(GRID_SIZE):
    merged = [False] * GRID_SIZE
    for row in range(1, GRID_SIZE):
      if self[row][col] != 0:
        k = row
        while k > 0 and self[k - 1][col] == 0:
          move = True
          self[k - 1][col] = self[k][col]
          self[k][col] = 0
          k -= 1
        if k > 0 and not merged[k - 1] and self[k - 1][col] == self[k][col]:
          move = True
          self[k - 1][col] *= 2
          self[k][col] = 0
          merged[k - 1] = True
          temp_score += self[row][k - 1]  # 更新积分
  return move, temp_score


def move_tiles_right(self):
  # 向右移动所有数字块
  move = False
  temp_score = 0
  for row in range(GRID_SIZE):
    merged = [False] * GRID_SIZE
    for col in range(GRID_SIZE - 2, -1, -1):
      if self[row][col] != 0:
        k = col
        while k < GRID_SIZE - 1 and self[row][k + 1] == 0:
          move = True
          self[row][k + 1] = self[row][k]
          self[row][k] = 0
          k += 1
        if k < GRID_SIZE - 1 and not merged[k + 1] and self[row][k + 1] == self[row][k]:
          move = True
          self[row][k + 1] *= 2
          self[row][k] = 0
          merged[k + 1] = True
          temp_score += self[row][k - 1]  # 更新积分
  return move, temp_score


def move_tiles_down(self):
  # 向下移动所有数字块
  move = False
  temp_score = 0
  for col in range(GRID_SIZE):
    merged = [False] * GRID_SIZE
    for row in range(GRID_SIZE - 2, -1, -1):
      if self[row][col] != 0:
        k = row
        while k < GRID_SIZE - 1 and self[k + 1][col] == 0:
          move = True
          self[k + 1][col] = self[k][col]
          self[k][col] = 0
          k += 1
        if k < GRID_SIZE - 1 and not merged[k + 1] and self[k + 1][col] == self[k][col]:
          move = True
          self[k + 1][col] *= 2
          self[k][col] = 0
          merged[k + 1] = True
          temp_score += self[row][k - 1]  # 更新积分
  return move, temp_score


def is_game_over(grid_):
  # 检查游戏是否结束（无法再移动数字块）
  for row in range(GRID_SIZE):
    for col in range(GRID_SIZE):
      if grid_[row][col] == 0:
        return False
      if col < GRID_SIZE - 1 and grid[row][col] == grid[row][col + 1]:
        return False
      if row < GRID_SIZE - 1 and grid[row][col] == grid[row + 1][col]:
        return False
  return True


def draw_grid():
  # 绘制游戏界面网格
  window.fill(BACKGROUND_COLOR)
  for row in range(GRID_SIZE):
    for col in range(GRID_SIZE):
      cell_value = grid[row][col]
      cell_color = get_cell_color(cell_value)
      cell_rect = pygame.Rect(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE)
      pygame.draw.rect(window, cell_color, cell_rect)
      if cell_value != 0:
        draw_text(cell_value, cell_rect)

  # 绘制积分
  score_text = font.render("Score: " + str(score), True, TEXT_COLOR)
  window.blit(score_text, (10, GRID_HEIGHT + 10))


def WindowUpdate():
  draw_grid()
  pygame.display.update()


def GetScreenShot():
  window = gw.getWindowsWithTitle('2048')
  window = window[0]
  print('位置:', window.left, window.top)
  print('大小:', window.width, window.height)
  region = (window.left, window.top, window.width, window.height)
  screenshot = pyautogui.screenshot(region=region)
  screenshot.save('result.png')


def Init():
  # 初始化Pygame
  pygame.init()

  # 创建游戏窗口
  global window
  window = pygame.display.set_mode((GRID_WIDTH, GRID_HEIGHT + 50))
  pygame.display.set_caption("2048")

  # 加载字体
  global font
  font = pygame.font.Font(None, 48)

  # 初始化游戏界面
  global grid
  grid = [[0] * GRID_SIZE for _ in range(GRID_SIZE)]
  add_new_tile()
  add_new_tile()

  # 分数
  global score
  score = 0

  # 绘制界面
  WindowUpdate()


def ManualOnKeyEvent(event):
  global score
  move = False
  if event.event_type == keyboard.KEY_DOWN:
    if event.name == 'a' or event.name == 'left':
      move, temp_score = move_tiles_left(grid)
      score += temp_score
    if event.name == 'd' or event.name == 'right':
      move, temp_score = move_tiles_right(grid)
      score += temp_score
    if event.name == 'w' or event.name == 'up':
      move, temp_score = move_tiles_up(grid)
      score += temp_score
    if event.name == 's' or event.name == 'down':
      move, temp_score = move_tiles_down(grid)
      score += temp_score
    if move:
      add_new_tile()
      # 测试自动化函数
      PredictBestMove(grid)
      # 绘制界面
      WindowUpdate()
      # 判断游戏是否结束
      if is_game_over(grid):
        print("游戏结束！")
        print("最终积分：", score)
        global game_exit
        game_exit = True


def AutoOnKeyEvent(event):
  global score
  direction = "left", "right", "up", "down"
  move = False
  if event.event_type == keyboard.KEY_DOWN:
    best_direction, null = PredictBestMove(grid, 1)
    print("最佳方向", best_direction)
    if best_direction == direction[0]:
      move, temp_score = move_tiles_left(grid)
      score += temp_score
    if best_direction == direction[1]:
      move, temp_score = move_tiles_right(grid)
      score += temp_score
    if best_direction == direction[2]:
      move, temp_score = move_tiles_up(grid)
      score += temp_score
    if best_direction == direction[3]:
      move, temp_score = move_tiles_down(grid)
      score += temp_score
    if move:
      add_new_tile()
      # 绘制界面
      WindowUpdate()
      if is_game_over(grid):
        print("游戏结束！")
        print("最终积分：", score)
        global game_exit
        game_exit = True


def FindFirstMaxValue(grid_):
  # 找到最大值
  max = 0  # 最大值
  max_i = 0  # 最大值坐标i
  max_j = 0  # 最大值坐标j
  for i in range(GRID_SIZE):
    for j in range(GRID_SIZE):
      if grid_[i][j] > max:
        max = grid_[i][j]
        max_i = i
        max_j = j
  return max, max_i, max_j
  print("第一个最大值是在第", max_i+1, "行第", max_j+1, "列的", max)


def GetEmptyNum(grid_):
  # 获取空格数量
  num = 0
  for i in range(GRID_SIZE):
    for j in range(GRID_SIZE):
      if grid_[i][j] == 0:
        num += 1
  return num


def CalculateContinuityPoint(grid_, flag_grid, i, j, prev_num):
  # 计算分数
  flag_grid[i][j] = 1
  if grid_[i][j] == 0:
    return 0
  if grid_[i][j] > prev_num:
    return 0
  up = 0
  down = 0
  left = 0
  right = 0
  if i > 0 and flag_grid[i-1][j] == 0:
    up = CalculateContinuityPoint(grid_, copy.deepcopy(flag_grid), i-1, j, grid_[i][j])
  if i < 3 and flag_grid[i+1][j] == 0:
    down = CalculateContinuityPoint(grid_, copy.deepcopy(flag_grid), i+1, j, grid_[i][j])
  if j > 0 and flag_grid[i][j-1] == 0:
    left = CalculateContinuityPoint(grid_, copy.deepcopy(flag_grid), i, j-1, grid_[i][j])
  if j < 3 and flag_grid[i][j+1] == 0:
    right = CalculateContinuityPoint(grid_, copy.deepcopy(flag_grid), i, j+1, grid_[i][j])
  return max(up, down, left, right) + grid_[i][j]


def GetGridSum(grid_):
  sum = 0
  for i in range(GRID_SIZE):
    for j in range(GRID_SIZE):
      sum += grid_[i][j]
  return sum


def CalculatePoint(grid_):
  max, max_i, max_j = FindFirstMaxValue(grid_)
  point_max_position = 0
  if max_i == 0:
    point_max_position += 1
  if max_j == 0:
    point_max_position += 1
  # print("最大值位置分数", point_max_position)

  empty_num = GetEmptyNum(grid_)
  if empty_num == 0:
    point_empty_num = 0
  else:
    point_empty_num = math.log(empty_num)
  # print("空格数量", empty_num)
  # print("空格数量分数", point_empty_num)

  flag_grid = [[0] * GRID_SIZE for _ in range(GRID_SIZE)]
  point_continuity = CalculateContinuityPoint(grid_, copy.deepcopy(flag_grid), max_i, max_j, max)
  # print("连续性分数为", point_continuity)

  grid_sum = GetGridSum(grid_)
  point_superfluous = point_continuity - grid_sum

  # print("得分为", score)

  # print("总分为", point_max_position * 1000 + point_empty_num * 10 + point_continuity + score * 0.001)
  # print(" ")

  global point_continuity_coefficient
  point_continuity_coefficient = 1
  return point_max_position * 1000 + point_empty_num * 10 + point_continuity * point_continuity_coefficient + score * 0.001


def PredictBestMovePoint(grid_, deep, alpha=-9999, beta=9999):
  move_function = move_tiles_left, move_tiles_right, move_tiles_up, move_tiles_down
  for i in range(4):
    temp_grid = copy.deepcopy(grid_)
    move, NULL = move_function[i](temp_grid)
    if move:
      if deep == 0:
        point = CalculatePoint(temp_grid)
      else:
        point = PredictionWorstGenerationPoint(temp_grid, deep, alpha, beta)
      if point > alpha:
        alpha = point
        if alpha >= beta:
          return alpha
  return alpha


def PredictionWorstGenerationPoint(grid_, deep, alpha=-9999, beta=9999):
  for i in range(GRID_SIZE):
    for j in range(GRID_SIZE):
      if grid_[i][j] == 0:
        # if (i > 0 and grid_[i-1][j] != 0) or (i < 3 and grid_[i+1][j] != 0) or (j > 0 and grid_[i][j-1] != 0) or (j < 3 and grid_[i][j+1] != 0):
        temp_grid = copy.deepcopy(grid_)
        for k in range(2):
          temp_grid[i][j] = 2 + k * 2
          point = PredictBestMovePoint(temp_grid, deep-1, alpha, beta)
          if point < beta:
            beta = point
            if alpha >= beta:
              return beta
  return beta


def PredictBestMove(grid_, deep, alpha=-9999, beta=9999):
  point = [-10000, -10000, -10000, -10000]
  direction = "left", "right", "up", "down"
  move_function = move_tiles_left, move_tiles_right, move_tiles_up, move_tiles_down
  for i in range(4):
    temp_grid = copy.deepcopy(grid_)
    move, NULL = move_function[i](temp_grid)
    # print("方向", direction[i], "是否移动", move)
    if move:
      if deep == 0:
        point[i] = CalculatePoint(temp_grid)
      else:
        point[i] = PredictionWorstGenerationPoint(temp_grid, deep, alpha, beta)
        if point[i] > alpha:
          alpha = point[i]
    # print("方向", direction[i], "得分", point[i])
  highest_point = max(point)
  best_direction = direction[point.index(highest_point)]
  # print("最佳方向", best_direction)
  return best_direction, highest_point


def ManualGame():
  keyboard.hook(ManualOnKeyEvent)
  game_exit = False
  while not game_exit:
    for event in pygame.event.get():
      if event.type == pygame.QUIT:
        game_exit = True


def ManualAutoGame():
  keyboard.hook(AutoOnKeyEvent)
  global game_exit
  game_exit = False
  while not game_exit:
    for event in pygame.event.get():
      if event.type == pygame.QUIT:
        game_exit = True


def AutoGame():
  direction = "left", "right", "up", "down"
  move_function = move_tiles_left, move_tiles_right, move_tiles_up, move_tiles_down
  global score
  global score_ave
  game_exit = False
  while not game_exit:
    for event in pygame.event.get():
      if event.type == pygame.QUIT:
        print("平均分：", score_ave)
        game_exit = True
    best_direction, NULL = PredictBestMove(grid, 1)
    # print("最佳方向", best_direction)
    move, temp_score = move_function[direction.index(best_direction)](grid)
    score += temp_score
    if move:
      add_new_tile()
      # 绘制界面
      WindowUpdate()
      if is_game_over(grid):
        print("游戏结束！")
        print("最终积分：", score)
        game_exit = True
        # if score < 94492:
        #   Init()
        # else:
        #   game_exit = True


def main():
  # 初始化
  Init()

  # 手动玩
  # ManualGame()

  # 键盘控制自动玩
  # ManualAutoGame()

  # 自动玩
  AutoGame()

  # 截图
  GetScreenShot()

  # 退出
  pygame.quit()


if __name__ == '__main__':
  main()
