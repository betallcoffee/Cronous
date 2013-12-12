/*
 Author : betallcoffee
 */

#ifndef __ET_MESSAGE_H__
#define __ET_MESSAGE_H__

#include <string>
#include <vector>
#include "ETBuffer.h"

class ETMessage {
public :
	ETMessage();
	ETMessage(int commandID, const std::string &data);
	ETMessage(int commandID, const char *data, size_t size); 
	~ETMessage();

	static ETMessage *createMessage(ETBuffer &buf);

	int getCategory() { return category_; }
	char *data() { return data_.peek(); }
	size_t size() { return data_.size(); }
	size_t track(size_t size) { return data_.track(size); }
	std::string content();

	//����ʧ��
	static const unsigned int kTypeSelfDeineMessageConnectFail = 0xfffffA01;
	//�����쳣�ж�
	static const unsigned int kTypeSelfDeineMessageConnectTerminate = 0xfffffA02;
	//�������ر�����
	static const unsigned int kTypeSelfDeineMessageServerCloseConnection = 0xfffffA03;
	//��Ϣ������ȥ���źźܲ
	static const unsigned int kTypeSelfDeineMessageConnotSendMessage = 0xfffffA04;
	//��ʾ������ܳ�������
	static const unsigned int kTypeSelfDeineMessageIdelTimeout = 0xfffffA05;
	//��ʾ������ܳ�������,�����˳�����¼
	static const unsigned int kTypeSelfDeineMessageReconnectHint = 0xfffffA06;
	//��ʾ������ܳ�������,�����˳�����¼
	static const unsigned int kTypeSelfDeineMessageReconnectForce = 0xfffffA07;
	//������ʾ
	static const unsigned int kTypeSelfDeineMessageErrorMessage = 0xfffffA08;
    //
	static const unsigned int kTypeSelfDeineMessageClientKillMessage = 0xfffffA09;

private :
	void initHead();

	static const int8_t head0_ = 78;
	static const int8_t head1_ = 37;
	static const int8_t head2_ = 38;
	static const int8_t head3_ = 48;
	static const int8_t protoVersion_ = 9;
	static const int32_t serverVersion_ = 0;

	int category_;
	ETBuffer data_; 
};

#endif // __ET_MESSAGE_H__
