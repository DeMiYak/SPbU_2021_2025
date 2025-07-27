import pandas as pd
import numpy as np
from scipy.interpolate import RBFInterpolator
import matplotlib.pyplot as plt

# Загрузка данных
train_data = pd.read_csv('field_train.csv')

# Выделение координат и интенсивности
latitude = train_data['latitude'].values
longitude = train_data['longitude'].values
intensity = train_data['intensity'].values

# Создание сетки координат
lat_grid = np.arange(34, 37.1, 0.1)  # Широта от 34 до 37 с шагом 0.1
lon_grid = np.arange(55, 60.1, 0.1)  # Долгота от 55 до 60 с шагом 0.1
lat_mesh, lon_mesh = np.meshgrid(lat_grid, lon_grid)

# Подготовка данных для интерполяции
points = np.column_stack((latitude, longitude))  # Координаты точек измерений
values = intensity  # Значения гравитационного поля

# Создание интерполятора
rbf = RBFInterpolator(points, values, kernel='cubic', epsilon=0.1)  # Можно выбрать 'linear', 'cubic', 'thin_plate_spline' и др.

# Интерполяция значений на сетке
grid_points = np.column_stack((lat_mesh.flatten(), lon_mesh.flatten()))
intensity_grid = rbf(grid_points).reshape(lat_mesh.shape)

# Создание DataFrame с предсказанными значениями
results = pd.DataFrame({
    'latitude': lat_mesh.flatten(),
    'longitude': lon_mesh.flatten(),
    'intensity': intensity_grid.flatten()
})

# Исключение точек, которые уже есть в field_train.csv
train_coords = set(zip(train_data['latitude'], train_data['longitude']))
results_filtered = results[~results.apply(lambda row: (row['latitude'], row['longitude']) in train_coords, axis=1)]

# Сохранение в файл
results_filtered.to_csv('answers.csv', index=False)

# Визуализация (опционально)
plt.figure(figsize=(10, 8))
plt.contourf(lon_mesh, lat_mesh, intensity_grid, levels=50, cmap='viridis')
plt.colorbar(label='Интенсивность гравитационного поля')
plt.scatter(longitude, latitude, c='red', s=10, label='Измеренные точки')
plt.xlabel('Долгота')
plt.ylabel('Широта')
plt.title('Гравитационная карта')
plt.legend()
plt.show()