---
sort: 2
---
# Mapping between Frames

从一个坐标系到另一个坐标系的变换用映射来描述。

运动包含平移和旋转。

## 坐标平移

$$
^A P  =  \ ^B P + \ ^A P_{B\_origin} 
$$

## 坐标旋转

$$
^A P  = \ ^A_B R \ ^B P 
$$


## 一般变换


$$
^A P  =  \ ^A_B R \ ^B P  + \ ^A P_{B\_origin} 
$$

先将 B 坐标系里的点变换到和 A 坐标系姿态相同，然后在进行远点平移。

写成矩阵形式

$$
\left [ 
    \begin{array}{}
        ^A P \\
        1        
    \end{array}    
\right] = \ 
\left [ 
    \begin{array}{}
        \ ^A_B R & \ ^A P_{B\_origin}  \\
        \boldsymbol{0}   & 1      
    \end{array}    
\right]
\left [ 
    \begin{array}{}
        ^B P \\
        1        
    \end{array}    
\right] 
$$

这就扩展成了一个 4*4 的矩阵了，这个矩阵方程的更简洁表达 $$ ^A P  = \ ^A_B T \ ^B P $$

这里这个矩阵就是齐次变换矩阵。

```note
知一直角坐标系中的某点坐标，则该点在另一直角坐标系中的坐标可通过齐次坐标变换求得。

所谓齐次坐标就是将一个原本是 n 维的向量用一个 n+1 维向量来表示。一个向量的齐次表示是不唯一的，比如齐次坐标[8,4,2]、[4,2,1]表示的都是二维点[2,1]。

齐次坐标提供了用矩阵运算把二维、三维甚至高维空间中的一个点集从一个坐标系变换到另一个坐标系的有效方法。
```

