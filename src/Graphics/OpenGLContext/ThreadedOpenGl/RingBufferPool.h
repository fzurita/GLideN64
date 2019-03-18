#pragma once

#include <memory>
#include <vector>
#include <atomic>


namespace opengl {
//This class is only thread safe for a single producer and single consumer
class PoolBufferPointer
{
public:
	PoolBufferPointer();
	PoolBufferPointer(const PoolBufferPointer& other);
	PoolBufferPointer& operator=(const PoolBufferPointer& other);

	bool isValid() const;
	size_t getSize() const;
private:
	PoolBufferPointer(size_t _offset, size_t _size, bool _isValid);

	size_t m_offset;
	size_t m_size;
	bool m_isValid;

	friend class RingBufferPool;
};

class RingBufferPool
{
public:

	RingBufferPool(size_t _poolSize);

	PoolBufferPointer createPoolBuffer(const char* _buffer, size_t _bufferSize);

	const char* getBufferFromPool(PoolBufferPointer _poolBufferPointer);

	void removeBufferFromPool(PoolBufferPointer _poolBufferPointer);

private:
	std::atomic<size_t> m_inUseStartOffset;
	std::atomic<size_t> m_inUseEndOffset;
	std::vector<char> m_poolBuffer;
};

}