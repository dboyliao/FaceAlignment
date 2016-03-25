# Face Alignment by Explicit Shape Regression - Cpp Implementation

This `README.md` is a summary of the algorithm introduced in this [paper](http://research.microsoft.com/pubs/192097/cvpr12_facealignment.pdf) by **Microsoft Research Asia**.

The original cpp implementation can be found in this github [repo](https://github.com/soundsilence/FaceAlignment).

# The Summary of Cpp Implemetation 

## Data Type

- `BoundingBox` (declared in `FaceAlignment.h`): it is an object which defines a rectangle box in the image.
    + `x`: the x-axis coordinate of the upper-left corner.
    + `y`: the y-axis coordinate of the upper-left corner.
    + `width`: the width of the rectangle.
    + `height`: the height of the rectangle.
    + `centroid_x`: the x-axis coordinate of the rectangle.
    + `centroid_y`: the y-axis coordinate of the rectangle.

- `FernCascade` (declared in `FernCascade.cpp`): the model used in the first stage boosting.
    + `Train`: the method used to train a cascade model consists of ferns.
    + `Predict`: predict the landmark given a image.
    + `Read`: load a trained model.
    + `Write`: write a trained model to disk.
    
*Go to [Implement Detail](#implementation-detail).*

- `Fern` (declared in `Fern.cpp`): the model used in in the second stage boosting.
    + `Train`: the method to train the fern model.
    + `Predict`: predict the landmark given a image.
    + `Read`: load a trained fern model.
    + `Write`: write a trained fern model to disk.

*Go to [Implement Detail](#implementation-detail).*

- `ShapeRegressor` (declared in `ShapeRegressor.cpp`): the shape regressor.
    + `Train`: training a shape regressor given images data.
    + `Predict`: predict the landmarks in a given image.
    + `Read`: load a trained shape regressor model.
    + `Write`: write a trained model to disk.

*Go to [Implement Detail](#implementation-detail).*

- `GetMeanShape` (declared in `Utils.cpp`)

Compute the mean shape of given landmarks among given images.

*Go to [Implement Detail](#implementation-detail).*

- `ProjectShape` (declared in `Utils.cpp`)

Normalize the landmarks. It will adjust the landmarks' coordinates to relative coordates with respect to given bounding boxes.

*Go to [Implement Detail](#implementation-detail).*

- `ReProjectShape` (declared in `Utils.cpp`)

Inverse function of `ProjectShape`.

*Go to [Implement Detail](#implementation-detail).*

- `SimilarityTransform` (declared in `Utils.cpp`)

Get the similarity transform (the scale and the rotation matrix) between two given shapes.

*Go to [Implement Detail](#implementation-detail).*

- `calculate_covariance` (declared in `Utils.cpp`)

Compute the covariance of two vectors.

*Go to [Implement Detail](#implementation-detail).*

## Implementation Detail

### Utils

- `ProjectShape`:
    + **Parameters**:
        * `shape` (`Mat_<double>`): a `2 x n` matrix where `n` is the number of landmarks and each row contains the `x` and `y` coordinates for each landmark.
        * `bounding_box` (`BoundingBox`): a rectangle where the `shape` lies in.
    + **Returns**:
        * `aligned_shape` (`Mat_<double>`): a aligned shape according to the bounding box.
    + **Pseudo Code**:
        1. Translate the landmark coordinates to the center of the bounding box, that is, making the center of the bounding box the origin of coordinates (align to the center of bounding box).
        2. Compute the ratio of centered coordinates to the width and height of the bounding box (normalization) and return the result.

- `ReProjectShape`:
    + **Parameters**:
        * `shape` (`Mat_<double>`): a `2 x n` matrix consisting of the aligned coordinates (See the **Pseudo Code** of `ProjectShape`).
        * `bounding_box` (`BoundingBox`): the target rectangle.
    + **Returns**:
        * `origin_shape`: the original shape in the target rectangle.
    + **Notes**:
        * Basically speaking, the `ReProjectShape` is a "reverse" version of `ProjectShape` (not exactly an inverse function in terms of the definition in math, but it is close).

Applying `ProjectShape` and `ReProjectShape` make sure that all the bounding boxes of each shape are aligned to the center.

- `GetMeanShape`:
    + **Parameters**:
        * `shapes` (`vector< Mat_<double> >`): a list of matrices which contains the coordinates of the landmarks (a `2 x n` matrix where `n` is the number of landmarks).
        * `bounding_box` (`vector< BoundingBox >`): a list of bounding boxes for each shape in `shapes`.
    + **Returns**:
        * `mean_shape` (`Mat_<double>`): the mean of aligned shape. (See the **Pseudo Code** for `ProjectShape` for detail of the normalization)

- `SimilarityTransform`:
    + **Parameters**:
        * `target_shape` (`Mat_<double>`): the target shape. It is a `2 x n` matrix consists of coordinates of landmarks.
        * `source_shape` (`Mat_<double>`): the source shape.
    + **Returns**:
        * `rotation`: the rotation matrix from normalized `source_shape` to normalized `target_shape`.
        * `scale`: the scale factor from normalized `source_shape` to normalized `target_shape`.
    + **Pseudo Code**:
        1. Make both `target_shape` and `source_shape` zero-mean.
        2. Compute the covariance matrix of demeaned `target_shape` and `source` shape.
        3. compute the `scale` by the norm of each shape matrix.
        4. compute the rotation matrix by the demeaned matrix.
        5. Return `rotation` and `scale`.

### Fern Cascade

- `Train`:
    + **Parameters**:
        * `images` (`vector< Mat_<uchar> >`): a list of matrices of pixel values of training images.
        * `current_shapes` (`vector< Mat_<double> >`)
        * `ground_truth_shapes` (`vector< Mat_<double> >`): the training shapes (landmarks labeled manually).
        * `bounding_box` (`vector< BoundingBox >`)
        * `mean_shape` (`Mat_<double>`): the mean shape of `ground_truth_shapes`.
        * `first_level_num` (`int`)
        * `second_level_num` (`int`)
        * `candidate_pixel_num` (`int`)
        * `curr_level_num` (`int`)
    + **Pseudo Code**:
        1. Initiate `candidate_pixel_differences` matrix (`2 x n_C` matrix where `n_c` is the number of candidate pixel) and `nearest_landmark_index` matrix (`1 x n_c`).
        2. Construct a list of shapes, `regression_targets`, and calculate its member as follow :
            - Find the rotation matrix, `rotation`, and scale, `scale`, from `mean_shape` to `current_shape` normalized to `bouding_box[i]`. 
            - `regression_target[i] = scale * rotation *  dS` where `dS` differences of `ground_truth_shape[i]` normalized to `bounding_box[i]` and `current_shapes[i]` normalized to `bounding_box[i]`.
        3. Find the candidate pixel locations as following:
            - pick a pixel in the normalized image lies in a unit circle as a candidate pixel.
            - find the landmark in the `mean_shape` which is the nearest one to the candidate pixel.
            - compute `(dx, dy)`, where `dx` and `dy` is the difference of the x and y coordinate of candidate pixel and its nearest landmark in the `meanshape`.
            - store the result in two list, `candidate_pixel_differences` and `nearest_landmark_index`, respectively.
        4. Compute the densities of the candidate pixels in each image, stored in `vector< vector<double> > densites`, as following. For `image_i`:
            -  Project `current_shape[i]` to `bounding_box[i]`.
            -  Compute the rotation matrix, `rotation`, and the scale, `scale` from `mean_shape` to `current_shape[i]`.
            -  apply the rotation matrix and scale to `candidate_pixel_differences[i]`.
            -  Find the x, y coordinate by scaled and rotated `candidate_pixel_differences[i]`.
            -  append the pixel value at that coordinate in `image[i]` to `densities[i]`.
        5. Construct the covariance matrix, `covariance`, a `n_c x n_c` matrix, where `covariance(i, j)` is the covariance of `densities[i]` and `densities[j]`. This is used for feature selection when training ferns.
        6. Train the ferns. (See [Fern: Train](#fern) for detail)

### Fern

Basically, we want to train a fern using pixel differences as features. That is, assign a pair of pixels, `(p1, p2)`, to every threshold and compute the intensity difference between these two pixels. If the differece exceeds the threshold, go to one branch, another if it is not.

The key here is that how to find proper pair for each threshold. See `Train` for detail.

- `Train`:
    + **Parameters**:
        * `candidate_pixel_intensity` (`vector< vector<double> >`): the `densities` in `FernCascade::Train`. It is the intensities
        * `covariance` (`Mat_<double>`): the covariane matrix of `candidate_pixel_intensity`.
        * `candidate_pixel_locations` (`Mat_<double>`): a `n_c x 2` matrix where `n_c` is the number of candidate pixels.
        * `nearest_landmark_index` (`Mat_<int>`): a `n_c x 1` matrix which each row is the index of the nearest landmark of corresponding candidate pixel.
        * `regression_target` (`vector< Mat_<double> >`): it is the difference of coordinates of candidate pixels between groudtruth shape and current shape. Note that both groudtruth shape and current shape have been aligned to the `mean_shape`.
        * `fern_pixel_num` (`int`): the depth of the fern. That is, the number of the thresholds.
    + `Pseudo Code`:
        1. Select `fern_pixel_num` many pixels pairs as following:
            - generate a random matrix of size `landmark_num x 2`, `random_direction`, and compute the inner product of it and each member in the `regression_targets` (the differece between current shape and groundtruth shape). Store the result in `projection_result`. (`images_num x 1` where `images_num` is the number of training images)
            - calculate the covariance of covariance between `projectoin_result` and each pixel intensity in `candidate_pixel_intensity`. Store the covariance in `covariance_projection_density`.
            - Find the pixel pair with max correlation as following:
                (Iterate over all possible `j` and `k`)
                + compute the covariance of `candidate_pixel_intensity[i] - candidate_pixel_intensity[j]`. This can be done by computing `covariance(i, i) + covariance(j, j) - 2*covariance(i, j)`. Let the value be `variance_pixel_difference`.
                + compute the correlation coefficient by `(covariance_projection_density(j) - covariance_projection_density(k))/(sqrt(variance_pixel_difference)* variance_projection_result` where `variance_projection_result` is the variance of `projection_result` we find above.
                + according to the correlation coefficient, find the "distinct" pairs with `fern_pixel_num` largest correlation.
                + Store the pair index in `selected_pixel_index_`, the location of selected pair in `selected_pixel_location` and its nearest landmark index in `selected_nearest_landmark_index`.
            - Among all training images, find the maximum difference of selected pixel pair in `selected_pixel_index`. Let the value be `max_diff`.
            - Set the threshold of this level in the fern by randomly choose on number among `(-0.2*max_diff, 0.2*max_diff)`.
        2. Fill the leaf node of the fern with a list of index of training images. The images are clustered according to the pixel differences of each selected pixel pair in `selected_pixel_index`.
        3. 

### Shape Regressor

- `Train`:
    + **Parameters**:
        * `images` (`vector< Mat_<uchar> >`): a list of matricex of pixel values of training images.
        * `ground_truth_shapes` (`vector< Mat_<double> >`): a list of matrices of coordinates of landmarks for each training image.
        * `bounding_box` (`vectro< BoundingBox >`): a list of bounding boxes for each training image.
        * `first_level_num` (`int`)
        * `second_level_num` (`int`)
        * `candidate_pixel_num` (`int`)
        * `fern_pixel_num` (`int`)
        * `initial_num` (`int`)
    + **Psudo Code**:
        1. Initialize `augmented_images`, `augmented_ground_truth_shapes`, `augmented_bounding_box` and `current_shapes` as following:
            1. For each `image_i` in `images`, randomly choose another image except `image_i`, say `image_j`, and append it to `augmented_images`.
            2. Append `image_i`'s ground truth shape and bounding box to `augmented_ground_truth_shapes` and `augmented_bounding_box`, respectively.
            3. Project `image_j` to its bounding box, `bounding_box_j`, with `ProjectShape` and then inverse project the relative coordinate back to `bounding_box_i`, the bounding box of `image_i` as initial value. Append it to `current_shapes`.
        2. Compute `mean_shape` of `ground_truth_shapes`.
        3. Training a Fern Cascade model, `fern_cascades`.

# References

- [Talk](http://techtalks.tv/talks/face-alignment-by-explicit-shape-regression/56379/)
- [Triangularization](http://www.geom.uiuc.edu/~samuelp/del_project.html)
- [Slides](http://www.slideshare.net/takmin/face-alignment-cvpr2012)
