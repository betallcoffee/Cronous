/*
 Author : Tina
 */

#include "ETMessage.h"

ETMessage::ETMessage() {
	initHead();
}

ETMessage::ETMessage(int commandID, const std::string &data) {
	initHead();
	int32_t a = data.length() + 4;
	data_.write(a);
	data_.write(static_cast<int32_t>(commandID));
	data_.write(data);
}

ETMessage::ETMessage(int commandID, const char *data, size_t size) {
	initHead();
	int32_t a = size + 4;
	data_.write(a);
	data_.write(static_cast<int32_t>(commandID));
	data_.write(data, size);
}

ETMessage::~ETMessage() {
}

ETMessage *ETMessage::createMessage(ETBuffer &buf) {
	buf.track(17);
	ETMessage *msg = new ETMessage(101, buf.peek(), buf.size());
	return msg;
}

std::string ETMessage::content() {
	return std::string(data_.peek() + 17, size());
}

void ETMessage::initHead() {
	data_.write(head0_);
	data_.write(head1_);
	data_.write(head2_);
	data_.write(head3_);
	data_.write(protoVersion_);
	data_.write(serverVersion_);
}
