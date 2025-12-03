#pragma once

#include "pch.h"

namespace Syn {

	template<class T>
	class CircularBuffer {
	protected:
		T* m_buffer = nullptr;
		size_t m_writePosition, m_count, m_size;
		void Advance() {
			if (!IsFull()) {
				m_count++;
			}
			m_writePosition = (m_writePosition + 1) % m_size;
		}
	public:
		CircularBuffer(size_t size) {
			m_buffer = new T[size];
			m_writePosition = 0;
			m_count = 0;
			m_size = size;
		}
		template<typename... Args>
		void Add(Args&&... args) {
			new (&m_buffer[m_writePosition]) T(static_cast<Args&&>(args)...);
			Advance();
		}
		T Get(const size_t index) const {
			if (IsFull()) {
				return m_buffer[(m_writePosition + index) % m_size];
			}
			else {
				return m_buffer[index];
			}
		}
		size_t Capacity() const {
			return m_size;
		}
		size_t Count() const {
			return m_count;
		}
		bool IsFull() const {
			return m_count == m_size;
		}
		void Initialize(const T value) {
			for (size_t i = 0; i < m_size; i++) {
				m_buffer[i] = value;
			}
		}
		~CircularBuffer() {
			delete m_buffer;
		}
	};

}