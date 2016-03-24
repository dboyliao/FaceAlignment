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
        * `shape` (`Mat_<double>`): a `n x 2` matrix where `n` is the number of landmarks and each row contains the `x` and `y` coordinates for each landmark.
        * `bounding_box` (`BoundingBox`): a rectangle where the `shape` lies in.
    + **Returns**:
        * `aligned_shape` (`Mat_<double>`): a aligned shape according to the bounding box.
    + **Notes**:
        1. Translate the landmark coordinates to the center of the bounding box, that is, making the center of the bounding box the origin of coordinates (align to the center of bounding box).
        2. Compute the ratio of centered coordinates to the width and height of the bounding box (normalization) and return the result.

- `ReProjectShape`:
    + **Parameters**:
        * `shape` (`Mat_<double>`): a `n x 2` matrix consisting of the aligned coordinates (See **Notes** for `ProjectShape`).
        * `bounding_box` (`BoundingBox`): the target rectangle.
    + **Returns**:
        * `origin_shape`: the original shape in the target rectangle.
    + **Notes**:
        * Basically speaking, the `ReProjectShape` is a "reverse" version of `ProjectShape` (not exactly an inverse function in terms of the definition in math, but it is close).

Applying `ProjectShape` and `ReProjectShape` make sure that all the bounding boxes of each shape are aligned to the center.

- `GetMeanShape`:
    + **Parameters**:
        * `shapes` (`vector< Mat_<double> >`): a list of matrices which contains the coordinates of the landmarks (a `n x 2` matrix where `n` is the number of landmarks).
        * `bounding_box` (`vector< BoundingBox >`): a list of bounding boxes for each shape in `shapes`.
    + **Returns**:
        * `mean_shape` (`Mat_<double>`): the mean of aligned shape. (See the **Notes** for `ProjectShape` for detail of the normalization)

- `SimilarityTransform`:
    + **Parameters**:
        * `target_shape` (`Mat_<double>`): the target shape. It is a `n x 2` matrix consists of coordinates of landmarks.
        * `source_shape` (`Mat_<double>`): the source shape.
    + **Returns**:
        * `rotation`: the rotation matrix from normalized `source_shape` to normalized `target_shape`.
        * `scale`: the scale factor from normalized `source_shape` to normalized `target_shape`.
    + **Notes**:
        1. Make both `target_shape` and `source_shape` zero-mean.
        2. Compute the covariance matrix of demeaned `target_shape` and `source` shape.
        3. compute the `scale` by the norm of each shape matrix.
        4. compute the rotation matrix by the demeaned matrix.
        5. Return `rotation` and `scale`.

## Fern Cascade

- `Train`:
    + **Parameters**:
        * 
