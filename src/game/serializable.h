#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

namespace Game
{
    /**
    \struct Serializable
    \brief Base class for serializable classes

    The Serializable class is mainly used to load and save
    a struct to a file. It is an abstract class that has to
    inherited, since different classes will have different
    data, and therefore implementation.
    */
    struct Serializable
    {
        virtual void WriteToFile(string fileName) = 0;
        virtual void ReadFromFile(string fileName) = 0;
    };
}
#endif // SERIALIZABLE_H
