import pygame
import random
import pygetwindow as gw
import pyautogui
import copy
import time

# 设置观测器
see_GetPoint_times = 0

# 设置输出
setting_print = False
setting_step_by_step = False
setting_deep = 0

# 设置游戏运行模式
# mode = "auto"
mode = "manual"

# 游戏界面大小
GRID_SIZE = 4
CELL_SIZE = 100
GRID_WIDTH = GRID_SIZE * CELL_SIZE
GRID_HEIGHT = GRID_SIZE * CELL_SIZE

# 颜色定义
BACKGROUND_COLOR = (187, 173, 160)
CELL_COLOR = (205, 193, 180)
TEXT_COLOR = (255, 255, 255)

# 初始化Pygame
pygame.init()

# 创建游戏窗口
window = pygame.display.set_mode((GRID_WIDTH, GRID_HEIGHT + 50))
pygame.display.set_caption("2048")

# 加载字体
font = pygame.font.Font(None, 48)

# 积分变量
score = 0


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


def AddNewTile(grid_, index, count):
  # 在指定位置生成一个指定数字
  for i in range(GRID_SIZE):
    for j in range(GRID_SIZE):
      if grid_[i][j] == 0:
        if index == 0:
          grid_[i][j] = 2 + count * 2
          return
        else:
          index -= 1


def move_tiles_left(self):
  # 向左移动所有数字块
  move = False
  global score
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
          score += self[row][k - 1]  # 更新积分
  return move


def move_tiles_up(self):
  # 向上移动所有数字块
  move = False
  global score
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
          score += self[k - 1][col]  # 更新积分
  return move


def move_tiles_right(self):
  # 向右移动所有数字块
  move = False
  global score
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
          score += self[row][k + 1]  # 更新积分
  return move


def move_tiles_down(self):
  # 向下移动所有数字块
  move = False
  global score
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
          score += self[k + 1][col]  # 更新积分
  return move


def is_game_over():
  # 检查游戏是否结束（无法再移动数字块）
  for row in range(GRID_SIZE):
    for col in range(GRID_SIZE):
      if grid[row][col] == 0:
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


# 初始化游戏界面
grid = [[0] * GRID_SIZE for _ in range(GRID_SIZE)]
add_new_tile()
add_new_tile()


def GetEmptyNum(self):
  # 获取空格数量
  num = 0
  for i in range(GRID_SIZE):
    for j in range(GRID_SIZE):
      if self[i][j] == 0:
        num += 1
  return num


def FindFirstMaxValue(self):
  # 找到最大值
  max = 0  # 最大值
  max_i = 0  # 最大值坐标i
  max_j = 0  # 最大值坐标j
  flag = [[0] * GRID_SIZE for _ in range(GRID_SIZE)]
  for i in range(GRID_SIZE):
    for j in range(GRID_SIZE):
      if self[i][j] > max:
        max = self[i][j]
        max_i = i
        max_j = j
  if setting_print:
    print("第一个最大值是在第", max_i+1, "行第", max_j+1, "列的", max)
  return max, max_i, max_j


def CalculatePoint(grid_, flag_grid, i, j, prev_num):
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
    up = CalculatePoint(grid_, copy.deepcopy(flag_grid), i-1, j, grid_[i][j])
  if i < 3 and flag_grid[i+1][j] == 0:
    down = CalculatePoint(grid_, copy.deepcopy(flag_grid), i+1, j, grid_[i][j])
  if j > 0 and flag_grid[i][j-1] == 0:
    left = CalculatePoint(grid_, copy.deepcopy(flag_grid), i, j-1, grid_[i][j])
  if j < 3 and flag_grid[i][j+1] == 0:
    right = CalculatePoint(grid_, copy.deepcopy(flag_grid), i, j+1, grid_[i][j])
  return max(up, down, left, right) + grid_[i][j]


def GetPoint(self):
  global see_GetPoint_times
  see_GetPoint_times += 1
  # 获取分数
  # max, max_i, max_j = FindFirstMaxValue(self)
  # point_max_position = 0
  # if max_i == 0:
  #   point_max_position = point_max_position + 1
  # if max_j == 0:
  #   point_max_position = point_max_position + 1
  # if setting_print:
  #   print("最大值位置分数", point_max_position)
  # empty_num = GetEmptyNum(self)
  # if empty_num == 0:
  #   point_empty_num = 0
  # else:
  #   point_empty_num = math.log(empty_num)
  # if setting_print:
  #   print("空格数量分数", point_empty_num)
  # flag_grid = [[0] * GRID_SIZE for _ in range(GRID_SIZE)]
  # point_continuity = CalculatePoint(self, copy.deepcopy(flag_grid), max_i, max_j, max)
  # if setting_print:
  #   print("连续性分数为", point_continuity)
  #   print("得分为", score)
  # return point_max_position * 1000 + point_empty_num * 10 + point_continuity + score * 0.001
  current_num = grid[0][0]
  point = current_num
  for i in range(GRID_SIZE):
    if i % 2 == 0:
      for j in range(GRID_SIZE):
        if i == 0 and j == 0:
          continue
        if grid[i][j] < current_num:
          point += grid[i][j]
        else:
          return point
    else:
      for j in range(GRID_SIZE-1, -1, -1):
        if grid[i][j] < current_num:
          point += grid[i][j]
        else:
          return point
  return point

def GetBestDirection(self, deep):
  # 找到最佳操作方向
  functions = [move_tiles_left, move_tiles_right, move_tiles_up, move_tiles_down]
  directions = ["left", "right", "up", "down"]
  point_list_sum = [0, 0, 0, 0]
  point_num_list = [0, 0, 0, 0]
  point_list = [0, 0, 0, 0]
  best_direction = ""
  for i in range(4):
    self_temp_1 = copy.deepcopy(self)
    if functions[i](self_temp_1):
      for j in range(GetEmptyNum(self_temp_1)):
        for k in range(2):
          self_temp_2 = copy.deepcopy(self_temp_1)
          AddNewTile(self_temp_2, j, k)
          if deep > 0:
            NULL, point_temp, point_num = GetBestDirection(self_temp_2, deep-1)
            point_num_list[i] += point_num
            point_list_sum[i] += point_temp
          else:
            point_temp = GetPoint(self_temp_2)
            point_num_list[i] += 1
            point_list_sum[i] += point_temp
            # if k == 0 and j == 0:
            # print("深度：", setting_deep - deep, "方向：", directions[i], "第", j+1, "个空格", "数字：", k*2+2, "分数：", point_temp)
  for i in range(4):
    if (point_num_list[i] == 0):
      point_list[i] = 0
    else:
      point_list[i] = point_list_sum[i] / point_num_list[i]
  # if setting_step_by_step and deep == setting_deep:
  # print("各方向得分为", point_list)
  point_num_sum = sum(point_num_list)
  best_point = max(point_list)
  point_sum = sum(point_list_sum)
  best_direction = directions[point_list.index(best_point)]
  # if setting_step_by_step and deep == setting_deep:
  # print("最佳方向为", best_direction)
  return point_list.index(best_point), point_sum, point_num_sum


# 游戏循环
running = True
direction, NULL, NULL = GetBestDirection(copy.deepcopy(grid), 0)
while running:
  # 处理事件
  for event in pygame.event.get():
    if event.type == pygame.QUIT:
      running = False
    # 手动模式
    elif mode == "manual":
      if event.type == pygame.KEYDOWN:
        if not is_game_over():
          if event.key == pygame.K_a or event.key == pygame.K_LEFT:
            move = move_tiles_left(grid)
            if move:
              add_new_tile()
          elif event.key == pygame.K_d or event.key == pygame.K_RIGHT:
            move = move_tiles_right(grid)
            if move:
              add_new_tile()
          elif event.key == pygame.K_w or event.key == pygame.K_UP:
            move = move_tiles_up(grid)
            if move:
              add_new_tile()
          elif event.key == pygame.K_s or event.key == pygame.K_DOWN:
            move = move_tiles_down(grid)
            if move:
              add_new_tile()  # 在移动后生成新数字块
        GetPoint(copy.deepcopy(grid))
        GetBestDirection(copy.deepcopy(grid), 0)
    # 自动模式
    elif mode == "auto":
      if not setting_step_by_step or event.type == pygame.KEYDOWN:
        if not is_game_over():
          functions = [move_tiles_left, move_tiles_right, move_tiles_up, move_tiles_down]
          move = functions[direction](grid)
          if move:
            add_new_tile()  # 在移动后生成新数字块
          empty_num = GetEmptyNum(grid)
          direction, NULL, NULL = GetBestDirection(copy.deepcopy(grid), 2)

  # 绘制界面
  draw_grid()
  pygame.display.update()
  time.sleep(0.1)

  if is_game_over():
    print("游戏结束！")
    print("最终积分：", score)
    break


def GetScreenShot():
  window = gw.getWindowsWithTitle('2048')
  window = window[0]
  print('位置:', window.left, window.top)
  print('大小:', window.width, window.height)
  region = (window.left, window.top, window.width, window.height)
  screenshot = pyautogui.screenshot(region=region)
  screenshot.save('result.png')


# 截图
GetScreenShot()

# 退出游戏
pygame.quit()
