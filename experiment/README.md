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

**See Implement Detail for detail.**

- `Fern` (declared in `Fern.cpp`): the model used in in the second stage boosting.
    + `Train`: the method to train the fern model.
    + `Predict`: predict the landmark given a image.
    + `Read`: load a trained fern model.
    + `Write`: write a trained fern model to disk.

**See Implement Detail for detail.**

- `ShapeRegressor` (declared in `ShapeRegressor.cpp`): the shape regressor.
    + `Train`: training a shape regressor given images data.
    + `Predict`: predict the landmarks in a given image.
    + `Read`: load a trained shape regressor model.
    + `Write`: write a trained model to disk.

**See Implement Detail for detail.**

- `GetMeanShape` (declared in `Utils.cpp`)

Compute the mean shape of given landmarks among given images.

**See Implement Detail for detail.**

- `ProjectShape` (declared in `Utils.cpp`)

Normalize the landmarks. It will adjust the landmarks' coordinates to relative coordates with respect to given bounding boxes.

**See Implement Detail for detail.**

- `ReProjectShape` (declared in `Utils.cpp`)

Inverse function of `ProjectShape`.

**See Implement Detail for detail.**

- `SimilarityTransform` (declared in `Utils.cpp`)

Get the similarity transform (the scale and the rotation matrix) between two given shapes.

**See Implement Detail for detail.**

- `calculate_covariance` (declared in `Utils.cpp`)

Compute the covariance of two vectors.

**See Implement Detail for detail.**

## Implementation Detail



