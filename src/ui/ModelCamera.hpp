#ifndef MODEL_CAMERA_HPP
#define MODEL_CAMERA_HPP

class ModelCamera {
    public:
        ModelCamera(float initialModelScale);
        ~ModelCamera();

        float getScale() const;
        float getX() const;
        float getY() const;

        void reset();
        void move(float x, float y); // Move the camera by (x,y)
        void scale(float scale); // Scale the modelScale by a factor of scale

    protected:
        float modelScale, initialModelScale; // pixels per game coord
        float cameraX, cameraY; // position of the center of the camera in game coords
};

#endif // MODEL_CAMERA_HPP
