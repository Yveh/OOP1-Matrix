# OOP1-Matrix

## 构造函数与赋值

1. 默认构造函数;

2. ```Matrix(std::size_t n, std::size_t m, T init = T())```,构造一个大小为 n × m 的矩阵,并将里面的每个元素初始化为 init

3. ```Matrix(std::initializer_list<std::initializer_list<T>>)```,利用给定的```initializer_list``` 来构造一个矩阵。

4. “拷贝”构造函数与赋值。要求如果可以用一个 T 来构造一个 V,则可以使用一个```Matrix<T>``` 来构造一个 ```Matrix<V>```。

5. “移动”构造函数与赋值。仅要求相同类型的移动构造。


## 元素获取

完成如下两个函数(请务必写对),它们用于获取矩阵的第 i 行 j 列的元素, ```0-based```。

1. ```T& operator()(std::size_t i, std::size_t j)```

2. ```const T& operator()(std::size_t, std::size_t) const```

并完成如下两个函数,返回矩阵的第 i 行/列。

1. ```Matrix<T> row(std::size_t i) const```

2. ```Matrix<T> column(std::size_t i) const```


## 运算

### 一元运算

1. ```-```,对矩阵中每个元素取负。

2. ```-=```

3. ```+=```

4. ```*=```,数乘

5. ```Matrix tran() const```,返回当前矩阵的转置矩阵。注:不改变当前矩阵。要求对于 += 等运算,支持 ```Matrix<int>+=``` 一个 ```Matrix<double>```


### 二元运算
1. ```==```,比较两个矩阵是否相同(元素的值相等即可)。

2. ```!=```,比较两个矩阵是否不同。

3. ```+```,定义为友元函数

4. ```-```,定义为友元函数

5. ```*```,数乘,定义为友元函数

6. ```*```,矩阵乘法,定义为友元函数。对于 ```Matrix<T> a``` 和 ```Matrix<V> b```,若 ```T + V``` 的类型为 ```U```,则 ```a+b``` 的返回值类型为```Matrix<U>(提示:decltype)```。回答问题:为何要定义为友元函数而非成员函数


## 迭代器

要求实现一个 ```random_access``` 的迭代器(具体要求见源代码),以及如下函数。

1. ```iterator begin()```

2. ```iterator end()```

3. ```T& operator*() const```,返回当前迭代器指向的数据。

4. ```* operator->() const```,返回迭代器的指针。

5. ```subMatrix(std::pair<std::size_t, std::size_t> l, std::pair<std::size_t,std::size_t> r)```。设 M 是当前矩阵的一个子矩阵,l 和 r 分别为它的左上角和右下角在原矩阵中的位置,返回 M 的 ```begin()``` 和 ```end()```。迭代器的移动不能超出范围。

以下是没有提到的函数。

1. ```++```,要求迭代器以行优先的方式进行移动。

2. ```--```,要求迭代器以行优先的方式进行移动。

3. ```+```,要求迭代器以行优先的方式进行移动。

4. ```-```,要求迭代器以行优先的方式进行移动。


## 其他

1. ```void clear()```,清空当前矩阵,并释放内存空间。

2. ```std::size_t rowlength()```,返回行数。

3. ```std::size_t columnlength()```,返回列数。

4. ```std::pair<std::size_t, std::size_t> size() const```,返回 ```size```。

5. ```void resize(std::size_t n, std::size_t m, T _init = T())```。 保留前 n × m 个元素,若元素不足则拿```_init``` 补充,并重新以行优先方式组成新矩阵。若元素个数相同,则不允许重新开设内存空间。

6. ```void resize(std::pair<std::size_t, std::size_t> sz, T _init= T())```。 要求同上。
