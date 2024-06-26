# Naive K-means algo
Organize your data into K sets. Single header file.

### Usage
Just drag the file into your project. 

### Options
 - define **T_K_MEANS_IMPL** to include the implementation for all the functions

 - define **MY_T_K_MEANS_SIZE_IMPL** to specify your own type for your data (typedef size_d_tim_ <your-type>). 
 Default is _int_. The file _main.c_ includes an example.


### Data structure
Your data should be arranged in a single array. All points must have the same dimensions (specified with the _dim_ argument).
Your data can have any type so long as you specify it with a typedef (check _main.c_ for an example).
It must have **_n_** * **_dim_** elements.

There must be two additional arrays. One of **_n_** elements (as many points as your _data_ array), sets.
The sets array contains the indexes of the sets each element belongs to.
If sets[2] = 7, then the third point in the dataset is currently in the 8th set.

The other array, **m** contains the current point each centroid is at and contains **_k_** * **_n_** elements.

You needn't worry about the details.
All you **DO NEED TO KNOW IS**:
 - **data** must be of size **_n_** * **_dim_** (number of points * number of dimensions of each point)
 - **sets** must be of size **_n_** (number of points) AND must be of type **_int_** (might change soon)
 - **m** must be of size **_k_** * **_dim_** (number of sets * number of dimensions of each point)

### Examples:

#### main.c

Check **_main.c_** out for a clear and simple example of this header's usage.
Compile it with 
```
make
```
and (optionally) specify INTERACTIVE=1 to step through each iteration manually.
```
make INTERACTIVE=1
```

##### main.c dependencies:
**_main.c_** depends on raylib to work. Since the lib isn't included in the project, you'll have to provide your own.
Raylib can be easily installed on Arch linux with 
```
sudo pacman -S raylib
```

If for some reason you can't get raylib working, **_main.c_** still serves as a great example.

#### [image palette](https://github.com/Timsousa1/image_palette)
A simple demonstration of a practical use-case for the k means algorithm.
It finds the best k colors to reconstruct the image with and creates a copy using only those k colors.
