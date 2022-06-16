# Audio Parser

This is a C++ implementation of a program to examine the content of the header of a .wav file.

.wav files are RIFF files (Resource Interchange File Format) which start out with a header followed by a sequence of data chunks.

The intent of this program is help finding out whether or not an audio file contains metadata stored at the end of it.

The audio file contains metadata at the end of it when there is a significant difference of size between the the Chunk Size (whose value 
is equal to the size of the whole file) and the Subchunk 2 Size (whose value is equal to the real audio data).

For more information about the RIFF file chunks and specifications: [The Canonical WAVE File Format](https://ccrma.stanford.edu/courses/422-winter-2014/projects/WaveFormat/#:~:text=The%20canonical%20WAVE%20format%20starts,the%20chunk%20following%20this%20number.)
