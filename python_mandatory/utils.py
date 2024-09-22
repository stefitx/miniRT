# utils.py
import numpy as np

def normalize(vector):
    """Returns the normalized vector."""
    norm = np.linalg.norm(vector)
    if norm == 0:
        return vector
    return vector / norm

def reflect(direction, normal):
    """Calculates the reflection direction."""
    return direction - 2 * np.dot(direction, normal) * normal
