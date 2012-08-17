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


/// 字符转换,将任意字节流转换成asc字符(如 [0x12,0x34] => "1234")
/**
 *
 * @param[IN]    hex_array      需要转换的数据
 * @param[IN]    hex_bytes      数据的长度(字节数)
 * @param[OUT]   out_buffer     输出缓冲区
 * @param[OUT]   upcase         输出结果是否大写
 * @param[OUT]   append_eof     输出结果是否补字符串结束符
 * 
 * @retval   指向out_buffer的指针
 * 
 *
 * @note 
 *     - out_buffer 的大小至少为hex_bytes的2倍,否则本函数行为不可预知
 *     - 本函数只转换字符,转换后的内容不含字符串结束符.
 */
char*	array_hex_to_asc(const void* hex_array,int hex_bytes,char* out_buffer,bool upcase=true,bool append_eof=true);


/// 字符转换,将asc流转换成hex(如 "1234" => [0x12,0x34])
/**
 *
 * @param[IN]    hexstr_array      需要转换的数据
 * @param[IN]    hexstr_bytes      数据的长度(字节数)
 * @param[OUT]   out_buffer     输出缓冲区
 * 
 * @retval   true 转换成功
 * @retval   false 转换失败
 * 
 *
 * @note 
 *     - hexstr_array 必须是[0 ~ 9]或者['A' ~ 'F']的字符数组,否则函数返回失败
 *     - hexstr_bytes 必须是偶数,否则函数返回失败.
 *     - out_buffer 的大小至少为 hexstr_bytes/2.
 */
bool	array_hexstr_to_hex(const void* hexstr_array,int hexstr_bytes,void* out_buffer);


/// 检查一个字节流数组中某一段数据是否为HEX格式的字符串
/**
 *
 * @param[IN]    hexstr_array      需要检查的数据
 * @param[IN]    start_offset      检查的起始位置
 * @param[OUT]   bytes_to_check    检查的字节数
 * 
 * @retval   true 被检查的区域是HEX格式的字符串
 * @retval   false 被检查的区域不是HEX格式的字符串
 * 
 * @note 
 *     - start_offset 必须大于或者等于 0 ,否则返回失败.
 *     - bytes_to_check.必须大于0,否则返回失败.
 */
bool	is_string_hex_format(const void* hexstr_array,int start_offset, int bytes_to_check);

/// 检查一个字节流数组中某一段数据是否为数字的字符串
/**
 *
 * @param[IN]    str_array         需要检查的数据
 * @param[IN]    start_offset      检查的起始位置
 * @param[OUT]   bytes_to_check    检查的字节数
 * 
 * @retval   true 被检查的区域是数字的字符串
 * @retval   false 被检查的区域不是数字的字符串
 * 
 * @note 
 *     - start_offset 必须大于或者等于 0 ,否则返回失败.
 *     - bytes_to_check.必须大于0,否则返回失败.
 */
bool	is_string_digital_format(const void* str_array,int start_offset, int bytes_to_check);

#endif // str_helper_h__