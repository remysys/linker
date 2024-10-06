import numpy as np

# 1. import pandas under the alias pd
import pandas as pd

# 2. print the version of pandas that has been imported
print(pd.__version__)

# 3. print out all the version information of the 
# libraries that are required by the pandas library
pd.show_versions()

"""
consider the following Python dictionary data and Python list labels:

data = {'animal': ['cat', 'cat', 'snake', 'dog', 'dog', 'cat', 'snake', 'cat', 'dog', 'dog'],
        'age': [2.5, 3, 0.5, np.nan, 5, 2, 4.5, np.nan, 7, 3],
        'visits': [1, 3, 2, 3, 2, 3, 1, 1, 2, 1],
        'priority': ['yes', 'yes', 'no', 'yes', 'no', 'no', 'no', 'yes', 'no', 'no']}

labels = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j']
(This is just some meaningless data I made up with the theme of animals and trips to a vet.)
"""

# 4. create a DataFrame df from this dictionary data which has the index labels

data = {'animal': ['cat', 'cat', 'snake', 'dog', 'dog', 'cat', 'snake', 'cat', 'dog', 'dog'],
        'age': [2.5, 3, 0.5, np.nan, 5, 2, 4.5, np.nan, 7, 3],
        'visits': [1, 3, 2, 3, 2, 3, 1, 1, 2, 1],
        'priority': ['yes', 'yes', 'no', 'yes', 'no', 'no', 'no', 'yes', 'no', 'no']}

labels = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j']

df = pd.DataFrame(data, index = labels)

#5. display a summary of the basic information about this DataFrame and its data 
#(hint: there is a single method that can be called on the DataFrame).

df.info()
df.describe()

# 6. return the first 3 rows of the DataFrame df.
print(print(df.iloc[:3]))
# or equivalently
print(df.head(3))

# 7. Select just the 'animal' and 'age' columns from the DataFrame df.
print(df.loc[:, ['animal', 'age']])
# or
print(df[['animal', 'age']])

# 8. select the data in rows [3, 4, 8] and in columns ['animal', 'age']
print(df.loc[df.index[[3, 4, 8]], ['animal', 'age']])

# 9. select only the rows where the number of visits is greater than 3.
print(df[df['visits'] > 3])

# 10. Select the rows where the age is missing, i.e. it is NaN.
print(df[df['age'].isna()])
# or
print(df[df['age'].isnull()])
