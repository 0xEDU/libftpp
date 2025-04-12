class DataBuffer {
	public:
		DataBuffer();
		DataBuffer(const DataBuffer &);            // Prevent copying
		DataBuffer &operator=(const DataBuffer &); // Prevent assignment
		~DataBuffer();
};
