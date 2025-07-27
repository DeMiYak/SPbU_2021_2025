import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import root_mean_squared_error
from sklearn.preprocessing import LabelEncoder

le = LabelEncoder()
labels = ['I', 'II', 'III', 'IV', 'V']
le.fit(labels)

trainData = pd.read_csv('train.csv')
testData = pd.read_csv('test.csv')

# Wrapping label transformation
trainData['B'] = le.transform(trainData['B'])
testData['B'] = le.transform(testData['B'])

attrTrain = trainData.drop('target', axis=1)
target = trainData['target']

attrTest = testData[['A', 'B', 'C', 'D', 'E', 'F']]

model = LinearRegression()
model.fit(attrTrain, target)
prediction = model.predict(attrTest)
testData['target']=prediction

# RMSE calc

attrTrain, attrTest, targetTrain, targetTest = train_test_split(
    trainData.drop('target', axis=1),
    trainData['target'],
    test_size=0.2,
    random_state=3
)

model.fit(attrTrain, targetTrain)
predTest = model.predict(attrTest)

rmse = root_mean_squared_error(targetTest, predTest)
print(f'RMSE = {rmse}, Score = {15*max(min((50-rmse)/40,1),0)}')

# Unwrapping label transformation
trainData['B'] = le.inverse_transform(trainData['B'])
testData['B'] = le.inverse_transform(testData['B'])

testData.to_csv('answers.csv', index=False)