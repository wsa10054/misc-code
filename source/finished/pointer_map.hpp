
/**
 * 
 * @file       blocking_pointer_map.h 	
 * @author     cj@sunnysec.com.cn
 * @date       2012-3-14
 *  
 * @brief      pointer map
 * 
 * @copyright <b>Copyright 2011 by sunnysec.com.cn(C) , All right reserved.</b> 
 */


#ifndef blocking_pointer_map_h__
#define blocking_pointer_map_h__


#include <boost/ptr_container/ptr_map.hpp>
#include <boost/utility.hpp>
#ifdef _DEBUG
#include <iostream>		//for cout
#endif // _DEBUG
#ifdef USING_BLOCKED_PTR_MAP__

#include <boost/thread.hpp>

#endif

#if (defined(_MSC_VER))
#pragma warning( push ) 
#pragma warning( disable : 4996 ) 
#endif // _MSVCR

/** 
 * @class    pointer_map
 *
 * @brief    ����MAP��ָ������ģ����.
 *
 * @warn    
 *     - �����Ҫ������ж�̬�ԵĶ���,��Ҫ�Զ����¡������
 *     - ʹ������Ҫ�����̰߳�ȫ����
 */
template 
<
	class KEY_TYPE,
	class T,
	class CloneAllocator = boost::heap_clone_allocator
>
class pointer_map:public boost::noncopyable
{
public:
	typedef pointer_map<KEY_TYPE,T,CloneAllocator>							this_type;
	typedef boost::ptr_map<KEY_TYPE,T,std::less<KEY_TYPE>,CloneAllocator>	container_type;
	typedef typename container_type::iterator								iterator;
	typedef typename container_type::const_iterator							const_iterator;
	typedef typename container_type::size_type								size_type;
	typedef typename container_type::value_type								container_value_type;


	typedef typename boost::call_traits<T>::param_type			param_type;
	typedef typename boost::call_traits<T>::reference			reference;
	typedef typename boost::call_traits<T>::const_reference		const_reference;
	typedef typename T											value_type;
	typedef typename boost::call_traits<T>::value_type			result_type;
	typedef	typename container_type::auto_type					auto_type;

	typedef typename T*											value_ptr;
	typedef typename const T*									const_value_ptr;
	typedef typename T&											value_ref;
	typedef typename const T&									const_value_ref;

	// 
public:

	pointer_map(void)
	{
#ifdef _DEBUG
		try_insert_=0;
#endif // _DEBUG
	}

	virtual ~pointer_map(void)
	{
		container_.release ();
#ifdef _DEBUG
		//std::cout<< "in pointer_map dtor: size :"<< (unsigned long)size() <<std::endl;
		//std::cout<< "try insert:"<< try_insert_ <<std::endl;
#endif // _DEBUG
	}

	
	/// ��ȡmap�Ĵ�С
	/**
	 * 
	 * @retval   size_type
	 * 
	 * @note this function <b>is not </b> thread-safe
	 */
	size_type	size() const
	{
		return container_.size ();
	}

	/// ����һ���µĶ���
	/**
	 *
	 * @param[IN]    key
	 * @param[IN]    val
	 * 
	 *
	 * @note 
	 *     - this function <b>is not</b> thread-safe
	 *     - igrone new one when the key is exists.
	 */
	void		insert(KEY_TYPE key,value_ptr val)
	{
		//std::map::insert() can not insert one  exists.
		container_.insert (key, val);
#ifdef _DEBUG
		++try_insert_;
#endif // _DEBUG
	}
	
	/// �ͷ�һ������,�ö�������������������ò��ұ�ɾ��.
	/**
	 *
	 * @param[IN]    key
	 *
	 * @note 
	 *     - this function <b>is not</b> thread-safe
	 *     - igrone new one when the key is exists.
	 */
	void		release_one(const KEY_TYPE& key)
	{
		if(exists(key)) 
			container_.release (container_.find(key));
	}
	
	/// �滻һ������
	/**
	 * description
	 *
	 * @param[IN]    key
	 * @param[IN]    val
	 * 
	 * @note this function <b>is</b> thread-safe
	 * @warn this function do nothing if the key not exists,and blocking_pointer_map will not delete the object(val), 
	 *       because the object has not been inserted.
	 */
	void		replace(KEY_TYPE key,param_type val)
	{
		if(exists(key)){
			release_one(key);
			insert(key,val);
		}
	}

	/// ���һ�������Ƿ��Ѿ�����(��keyΪ����)
	/**
	 * description
	 *
	 * @param[IN]    key
	 * @note this function <b>is not</b> thread-safe
	 */
	bool		exists(KEY_TYPE key)const
	{
		return container_.find (key) != container_.end ();
	}

	/// ����һ������
	/**
	 *
	 * @param[IN]    key
	 * @retval   value_ptr when found.
	 * @retval   NULL when not found.
	 * 
	 * @note this function <b>is not</b> thread-safe
	 */
	value_ptr		find(KEY_TYPE key) 
	{
		iterator it = container_.find(key);
		return (container_.end() == it)?(value_ptr(NULL)):(it->second);
	}
	const value_ptr		find(KEY_TYPE key) const
	{
		const_iterator c_it = container_.find(key);
		return (container_.end() == c_it)?( value_ptr(NULL)):(it->second);
	}
	
	/// ������ begin
	/**
	 * 
	 * @note this function <b>is not</b> thread-safe
	 */
	iterator		begin()
	{
		return container_.begin();
	}
	/// ֻ�������� begin
	/**
	 * 
	 * @note this function <b>is not</b> thread-safe
	 */
	const_iterator		begin()const
	{
		return container_.begin();
	}
	/// ������ end
	/**
	 * 
	 * @note this function <b>is not</b> thread-safe
	 */
	iterator		end()
	{
		return container_.end();
	}
	/// ֻ�������� end
	/**
	 * 
	 * @note this function <b>is not</b> thread-safe
	 */
	const_iterator		end()const
	{
		return container_.end();
	}
	/// �ͷ����Զ���
	/**
	 *
	 * @note 
	 *     - this function <b>is not</b> thread-safe
	 */
	void			release_all()
	{
		container_.release ();
	}
	/// get a copy of all objects .


	
	/// ȡ��һ�ݿ�¡
	/**
	 *
	 * @param[OUT]   new_one
	 * @note 
	 *     - this function <b>is not</b> thread-safe
	 */
	
	this_type*		clone_new()
	{
		this_type* new_one=new this_type();
		if(size() > 0){
			//deep copy
			new_one->container_=this->container_;
		}
		return new_one;
	}
	
	void		clone_new(this_type& new_one)
	{
		new_one.release_all ();
		if(size() > 0){
			//deep copy
			new_one.container_=this->container_;
		}
	}
protected:
	container_type&	get_container()
	{
		return container_;
	}
private:
	container_type	container_;
#ifdef _DEBUG
	unsigned long long			try_insert_;
#endif // _DEBUG
};

#ifdef USING_BLOCKED_PTR_MAP__


/** 
 * @class    blocking_pointer_map
 *
 * @brief    ����MAP��������ָ������.
 *
 * @note     
 *     - blocking_object_pool �ǻ���std::map���������ָ���.
 *     - blocking_object_pool �����·���<b>����</b>�̰߳�ȫ��:
 *         -# ���������ʺ���:begin,end.
 *     - blocking_object_pool ʹ�ö�д����֤�󲿷ֺ������̰߳�ȫ��.
 *     - ���÷��̰߳�ȫ�ķ�ʽʱ,�ⲿʹ�÷����Խ���get_mutex ��ʵ���̰߳�ȫ.
 *     - �ṩ���������ʺ�����Ҫ����ĳЩ����¶���Դ����Ҫ��ϸߵ����,���û������������,ʹ��clone
 *       ��������ȡһ�ݿ���,Ȼ��Ͳ���Ҫ������Դ��������,����ʹ��һЩ���̰߳�ȫ�ķ�����.
 */
template 
<
	class KEY_TYPE,
	class T,
	class CloneAllocator = boost::heap_clone_allocator
>
class blocking_pointer_map:public pointer_map<KEY_TYPE,T,CloneAllocator>
{
public:
	typedef	pointer_map<KEY_TYPE,T,CloneAllocator>					impl;
	typedef blocking_pointer_map<KEY_TYPE,T,CloneAllocator>			this_type;
	typedef boost::ptr_map<KEY_TYPE,T,std::less<KEY_TYPE>,CloneAllocator> container_type;
	typedef	boost::shared_mutex									mutex_type;
	typedef	boost::shared_lock<mutex_type>						read_lock;
	typedef	boost::unique_lock<mutex_type>						write_lock;
	// 
public:

	blocking_pointer_map(void)
	{
	}

	virtual ~blocking_pointer_map(void)
	{
		container_.release_all ();
	}

	
	/// ȡ��mutex ����
	/**
	 * ������Ϊ�ⲿʹ�����ṩһ�������,��ʹ�����ܹ������̰߳�ȫ��.
	 *
	 * @retval   mutex_type
	 * 
	 *
	 * @par Example
	 * ʹ��ʾ��:
	 * @code
	 * typedef blocking_pointer_map<int,int> int_ptr_map;
	 * int_ptr_map.obj_map;
	 * boost::shared_lock<int_ptr_map::mutex_type> r_lock(obj_map.get_mutex());
	 * int_ptr_map::const_iterator c_it=obj_map.begin();
	 * while(c_it != obj_map.end()){
	 *     c_it++;
	 *     use_iterator();
	 * }
	 * @endcode
	 *
	 * @note this function <b>is</b> thread-safe
	 */
	mutex_type&	get_mutex()
	{
		return container_mutex_;
	}

	
	/// ��ȡmap�Ĵ�С
	/**
	 * 
	 * @retval   size_type
	 * 
	 * @note this function <b>is </b> thread-safe
	 */
	size_type	size()
	{
		read_lock lock(container_mutex_);
		return container_.size ();
	}

	/// ����һ���µĶ���
	/**
	 *
	 * @param[IN]    key
	 * @param[IN]    val
	 * 
	 *
	 * @note 
	 *     - this function <b>is</b> thread-safe
	 *     - igrone new one when the key is exists.
	 */
	void		insert(KEY_TYPE key,value_ptr val)
	{
		write_lock lock(container_mutex_);
		container_.insert (key, val);
	}
	
	/// �ͷ�һ������,�ö�������������������ò��ұ�ɾ��.
	/**
	 *
	 * @param[IN]    key
	 *
	 * @note 
	 *     - this function <b>is</b> thread-safe
	 *     - igrone new one when the key is exists.
	 */
	void		release_one(const KEY_TYPE& key)
	{
		write_lock lock(container_mutex_);
		container_.release_one (key);
	}
	
	/// �滻һ������
	/**
	 * description
	 *
	 * @param[IN]    key
	 * @param[IN]    val
	 * 
	 * @note this function <b>is</b> thread-safe
	 * @warn this function do nothing if the key not exists,and blocking_pointer_map will not delete the object(val), 
	 *       because the object has not been inserted.
	 */
	void		replace(KEY_TYPE key,param_type val)
	{
		write_lock lock(container_mutex_);
		container_.replace(key,val);
	}

	/// ���һ�������Ƿ��Ѿ�����(��keyΪ����)
	/**
	 * description
	 *
	 * @param[IN]    key
	 * @note this function <b>is</b> thread-safe
	 */
	bool		exists(KEY_TYPE key)
	{
		read_lock lock(container_mutex_);
		return container_.exists (key);
	}

	/// ����һ������
	/**
	 *
	 * @param[IN]    key
	 * @retval   value_ptr when found.
	 * @retval   NULL when not found.
	 * 
	 * @note this function <b>is</b> thread-safe
	 */
	value_ptr		find(KEY_TYPE key)
	{
		read_lock lock(container_mutex_);
		return container_.find(key);
	}

	
	/// ������ begin
	/**
	 * 
	 * @note this function <b>is not</b> thread-safe
	 */
	iterator		begin()
	{
		return container_.begin();
	}
	/// ֻ�������� begin
	/**
	 * 
	 * @note this function <b>is not</b> thread-safe
	 */
	const_iterator		begin()const
	{
		return container_.begin();
	}
	/// ������ end
	/**
	 * 
	 * @note this function <b>is not</b> thread-safe
	 */
	iterator		end()
	{
		return container_.end();
	}
	/// ֻ�������� end
	/**
	 * 
	 * @note this function <b>is not</b> thread-safe
	 */
	const_iterator		end()const
	{
		return container_.end();
	}
	/// �ͷ����Զ���
	/**
	 *
	 * @note 
	 *     - this function <b>is</b> thread-safe
	 */
	void			release_all()
	{
		write_lock lock(container_mutex_);
		container_.release_all ();
	}
	/// get a copy of all objects .


	
	/// ȡ��һ�ݿ�¡
	/**
	 *
	 * @param[OUT]   new_one
	 * @note 
	 *     - this function <b>is</b> thread-safe
	 */
	
	this_type*		clone_new()
	{
		this_type* new_one=new this_type();
		if(size() > 0){
			read_lock lock(container_mutex_);
			//deep copy
			this->container_.clone_new(new_one->container_);
		}
		return new_one;
	}
	void		clone_new(this_type& new_one)
	{
		new_one.release_all ();
		if(size() > 0){
			//deep copy
			this->container_.clone_new(new_one.container_);
		}
	}
private:
	impl			container_;
	mutex_type		container_mutex_;
};
#endif // USING_BLOCKED_PTR_MAP__

#if (defined(_MSC_VER))
#pragma warning( pop ) 
#endif // _MSVCR

#endif // blocking_pointer_map_h__
