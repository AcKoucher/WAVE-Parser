#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Header
{
	unsigned char	chunkID[4];
	unsigned int	chunkSize;
	unsigned char	format[4];
	unsigned char	subChunkOneID[4];
	unsigned int	subChunkOneSize;
	unsigned short	audioFormat;
	unsigned short	numChannels;
	unsigned int	sampleRate;
	unsigned int	byteRate;
	unsigned short	blockAlign;
	unsigned short	bitPerSample;
	unsigned short	extraParamSize;
	std::vector<unsigned char> extraParam;
	unsigned char	subChunkTwoID[4];
	unsigned int	subChunkTwoSize;
	std::vector<unsigned char> audio;
};

bool RiffChecker(Header& header)
{
	if (header.chunkID[0] != 'R' && header.chunkID[1] != 'I' && header.chunkID[2] != 'F' && header.chunkID[3] != 'F')
		return false;
	else
		return true;
}

void PrintHeader(Header& parsedHeader)
{
	std::cout << "Chunk ID: ";
	std::cout << parsedHeader.chunkID[0];
	std::cout << parsedHeader.chunkID[1];
	std::cout << parsedHeader.chunkID[2];
	std::cout << parsedHeader.chunkID[3] << std::endl;
	std::cout << "Chunk Size: ";
	std::cout << parsedHeader.chunkSize << " bytes" << std::endl;
	std::cout << "Format: ";
	std::cout << parsedHeader.format[0];
	std::cout << parsedHeader.format[1];
	std::cout << parsedHeader.format[2];
	std::cout << parsedHeader.format[3] << std::endl;

	std::cout << "Subchunk 1 ID: ";
	std::cout << parsedHeader.subChunkOneID[0];
	std::cout << parsedHeader.subChunkOneID[1];
	std::cout << parsedHeader.subChunkOneID[2];
	std::cout << parsedHeader.subChunkOneID[3] << std::endl;
	std::cout << "Subchunk 1 Size: ";
	std::cout << parsedHeader.subChunkOneSize << " bytes" << std::endl;
	std::cout << "Audio Format: ";
	std::cout << parsedHeader.audioFormat << std::endl;
	std::cout << "Number of Channels: ";
	std::cout << parsedHeader.numChannels << std::endl;
	std::cout << "Sample Rate: ";
	std::cout << parsedHeader.sampleRate << " Hz" << std::endl;
	std::cout << "Byte Rate: ";
	std::cout << parsedHeader.byteRate << std::endl;
	std::cout << "Block Align: ";
	std::cout << parsedHeader.blockAlign << std::endl;
	std::cout << "Bits per Sample: ";
	std::cout << parsedHeader.bitPerSample << " bits" << std::endl;

	std::cout << "Subchunk 2 ID: ";
	std::cout << parsedHeader.subChunkTwoID[0];
	std::cout << parsedHeader.subChunkTwoID[1];
	std::cout << parsedHeader.subChunkTwoID[2];
	std::cout << parsedHeader.subChunkTwoID[3] << std::endl;
	std::cout << "Subchunk Two Size (audio): ";
	std::cout << parsedHeader.subChunkTwoSize << " bytes" << std::endl;
}

void Initialize(std::string& userInputPath)
{
	std::cout << "Welcome to Audio Parser!" << std::endl;
	std::cout << std::endl;
	std::cout << "This software was made to examine the information stored " << std::endl;
	std::cout << "in the header of the so called RIFF files." << std::endl;
	std::cout << std::endl;
	std::cout << "The path of the file must be written such as the example below." << std::endl;
	std::cout << "Example: C:\\\\Paste\\\\file.wav" << std::endl;
	std::cout << std::endl;
	std::cout << "Please, type the path of the file that you want to parse:" << std::endl;
	std::cin >> userInputPath;
	std::cout << std::endl;
}

int main()
{
	unsigned char audioByte;
	unsigned char extraParamByte;
	std::string filePath;
	Header fileHeader;
	bool checksRiff;

	Initialize(filePath);

	std::ifstream file(filePath, std::ios::binary);

	file.read((char*)&fileHeader.chunkID, 4);

	checksRiff = RiffChecker(fileHeader);
	if (!checksRiff)
	{
		std::cout << "[ERROR]: The file you are trying to parse is not a RIFF file or the path is invalid!" << std::endl;
		return EXIT_FAILURE;
	}

	file.read((char*)&fileHeader.chunkSize, 4);
	file.read((char*)&fileHeader.format, 4);

	file.read((char*)&fileHeader.subChunkOneID, 4);
	file.read((char*)&fileHeader.subChunkOneSize, 4);
	file.read((char*)&fileHeader.audioFormat, 2);
	file.read((char*)&fileHeader.numChannels, 2);
	file.read((char*)&fileHeader.sampleRate, 4);
	file.read((char*)&fileHeader.byteRate, 4);
	file.read((char*)&fileHeader.blockAlign, 2);
	file.read((char*)&fileHeader.bitPerSample, 2);

	if (fileHeader.subChunkOneSize > 16)
	{
		file.read((char*)&fileHeader.extraParamSize, 2);

		for (int i = 0; i < fileHeader.extraParamSize; i++)
		{
			file.read((char*)&extraParamByte, 1);
			fileHeader.extraParam.push_back(extraParamByte);
		}
	}

	file.read((char*)&fileHeader.subChunkTwoID, 4);
	file.read((char*)&fileHeader.subChunkTwoSize, 4);

	for (int j = 0; j < fileHeader.subChunkTwoSize; j++)
	{
		file.read((char*)&audioByte, 1);
		fileHeader.audio.push_back(audioByte);
	}

	PrintHeader(fileHeader);

	std::cin.get();
}