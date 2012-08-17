#ifndef str_helper_h__
#define str_helper_h__


inline	bool	is_degital(char c){
	return (c >= '0' && c <= '9');
}
inline	bool	is_a2f(char c){
	return (c >= 'a' && c <= 'f') || ( c >= 'A' && c <= 'F' );
}
inline	bool	is_a2z(char c){
	return (c >= 'a' && c <= 'z') || ( c >= 'A' && c <= 'Z' );
}
inline bool hex_value(char asc_char,unsigned char& out){
	if ( asc_char >= '0' && asc_char <= '9' ){
		out= asc_char - '0';
		return true;
	}else if(asc_char >= 'A' && asc_char <= 'F'){
		out= asc_char - 'A' + 10;
		return true;
	}else if(asc_char >= 'a' && asc_char <= 'f'){
		out= asc_char - 'a' + 10;
		return true;
	}else {
		return false;
	}

}


/// �ַ�ת��,�������ֽ���ת����asc�ַ�(�� [0x12,0x34] => "1234")
/**
 *
 * @param[IN]    hex_array      ��Ҫת��������
 * @param[IN]    hex_bytes      ���ݵĳ���(�ֽ���)
 * @param[OUT]   out_buffer     ���������
 * @param[OUT]   upcase         �������Ƿ��д
 * @param[OUT]   append_eof     �������Ƿ��ַ���������
 * 
 * @retval   ָ��out_buffer��ָ��
 * 
 *
 * @note 
 *     - out_buffer �Ĵ�С����Ϊhex_bytes��2��,���򱾺�����Ϊ����Ԥ֪
 *     - ������ֻת���ַ�,ת��������ݲ����ַ���������.
 */
char*	array_hex_to_asc(const void* hex_array,int hex_bytes,char* out_buffer,bool upcase=true,bool append_eof=true);


/// �ַ�ת��,��asc��ת����hex(�� "1234" => [0x12,0x34])
/**
 *
 * @param[IN]    hexstr_array      ��Ҫת��������
 * @param[IN]    hexstr_bytes      ���ݵĳ���(�ֽ���)
 * @param[OUT]   out_buffer     ���������
 * 
 * @retval   true ת���ɹ�
 * @retval   false ת��ʧ��
 * 
 *
 * @note 
 *     - hexstr_array ������[0 ~ 9]����['A' ~ 'F']���ַ�����,����������ʧ��
 *     - hexstr_bytes ������ż��,����������ʧ��.
 *     - out_buffer �Ĵ�С����Ϊ hexstr_bytes/2.
 */
bool	array_hexstr_to_hex(const void* hexstr_array,int hexstr_bytes,void* out_buffer);


/// ���һ���ֽ���������ĳһ�������Ƿ�ΪHEX��ʽ���ַ���
/**
 *
 * @param[IN]    hexstr_array      ��Ҫ��������
 * @param[IN]    start_offset      ������ʼλ��
 * @param[OUT]   bytes_to_check    �����ֽ���
 * 
 * @retval   true ������������HEX��ʽ���ַ���
 * @retval   false ������������HEX��ʽ���ַ���
 * 
 * @note 
 *     - start_offset ������ڻ��ߵ��� 0 ,���򷵻�ʧ��.
 *     - bytes_to_check.�������0,���򷵻�ʧ��.
 */
bool	is_string_hex_format(const void* hexstr_array,int start_offset, int bytes_to_check);

/// ���һ���ֽ���������ĳһ�������Ƿ�Ϊ���ֵ��ַ���
/**
 *
 * @param[IN]    str_array         ��Ҫ��������
 * @param[IN]    start_offset      ������ʼλ��
 * @param[OUT]   bytes_to_check    �����ֽ���
 * 
 * @retval   true ���������������ֵ��ַ���
 * @retval   false ���������������ֵ��ַ���
 * 
 * @note 
 *     - start_offset ������ڻ��ߵ��� 0 ,���򷵻�ʧ��.
 *     - bytes_to_check.�������0,���򷵻�ʧ��.
 */
bool	is_string_digital_format(const void* str_array,int start_offset, int bytes_to_check);

#endif // str_helper_h__