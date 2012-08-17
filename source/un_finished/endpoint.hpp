#include <netinet/in.h>
#include <arpa/inet.h> 
#include <string>
#include <assert.h>

namespace endpoint
{
	namespace ip_address
	{
		/// ipv4 address,see netinet/in.h
		typedef struct  in_addr   ip_addr_v4;
		/// ipv6 address,see netinet/in.h
		typedef struct  in6_addr  ip_addr_v6;
		
		/// fully ipv4 address,see netinet/in.h
		typedef struct  sockaddr_in   addr_v4;
		/// fully ipv6 address,see netinet/in.h
		typedef struct  sockaddr_in6  addr_v6;
		
		/// return : 
		///     1       ok
		///     0       ip is not a valid ip address string
		///     -1      address family not valid
		static int ip4_string_to_inaddr(const std::string& ip,ip_addr_v4* out_buffer)
		{
			int result=1;
			
			if(ip.length() > 0){
				memset(&(out_buffer->in_addr),0,sizeof(out_buffer->in_addr));
				result = ::inet_ntop(AF_INET,ip.cstr(),out_buffer);
			}else{
				*out_buffer = INADDR_ANY;
			}
			return result;
		}
		
		/// return : 
		///     1       ok
		///     0       ip is not a valid ip address string
		///     -1      address family not valid
		static int ip6_string_to_inaddr(const std::string& ip,ip_addr_v6* out_buffer)
		{
			int result=1;
			
			if(ip.length() > 0){
				memset(&(out_buffer->in_addr),0,sizeof(out_buffer->in_addr));
				result = ::inet_ntop(AF_INET6,ip.cstr(),out_buffer);
			}else{
				memcpy(out_buffer,in6addr_any,sizeof(ip_addr_v6));
			}
			return result;
		}
		
		class ipv4
		{
		public:
			ipv4(const std::string& ip,unsigned short port)
			{
				int ret=ip4_string_to_inaddr(ip,&(m_addr.sin_addr));
				assert(1 == ret);
				m_addr.port=::htons(port);
				(void)ret;
			}
			ipv4(const std::string& ip)
			{
				int ret=ip4_string_to_inaddr(ip,&(m_addr.sin_addr));
				assert(1 == ret);
				m_addr.port=::htons(0);
				(void)ret;
			}
			ipv4(unsigned short port)
			{
				int ret=ip4_string_to_inaddr("",&(m_addr.sin_addr));
				assert(1 == ret);
				m_addr.port=::htons(port);
				(void)ret;
			}
			ipv4()
			{
				int ret=ip4_string_to_inaddr("",&(m_addr.sin_addr));
				assert(1 == ret);
				m_addr.port=::htons(0);
				(void)ret;
			}
			
			const addr_v4&		addr_t()const 
			{
				return m_addr;
			}
			addr_v4&		addr_t() 
			{
				return m_addr;
			}
			
			std::string		ip()const
			{
				char ip[100]={0};
				const char * ret = ::inet_ntop(AF_INET,&(m_addr.sin_addr),(int)(sizeof(ip_addr_v4)));
				return ret?std::string(ret):std::string("");
			}
			
			unsigned short port()const
			{
				return ::ntohs(m_addr.port);
			}
		private:
			addr_v4 m_addr;
		}
#if 0		
		class ipv6
		{
		public:
			ipv6(const std::string& ip,unsigned short port)
			{
				int ret=ip4_string_to_inaddr(ip,&(m_addr.sin_addr));
				assert(1 == ret);
				m_addr.port=::htons(port);
				(void)ret;
			}
			ipv6(const std::string& ip)
			{
				int ret=ip4_string_to_inaddr(ip,&(m_addr.sin_addr));
				assert(1 == ret);
				m_addr.port=::htons(0);
				(void)ret;
			}
			ipv6(unsigned short port)
			{
				int ret=ip4_string_to_inaddr("",&(m_addr.sin_addr));
				assert(1 == ret);
				m_addr.port=::htons(port);
				(void)ret;
			}
			ipv6()
			{
				int ret=ip4_string_to_inaddr("",&(m_addr.sin_addr));
				assert(1 == ret);
				m_addr.port=::htons(0);
				(void)ret;
			}
			const addr_v6&		addr_t()const 
			{
				return m_addr;
			}
			addr_v6&		addr_t() 
			{
				return m_addr;
			}
			std::string		ip()const
			{
				char ip[100]={0};
				const char * ret = ::inet_ntop(AF_INET6,&(m_addr.sin_addr),(int)(sizeof(ip_addr_v6)));
				return ret?std::string(ret):std::string("");
			}
			
			unsigned short port()const
			{
				return ::ntohs(m_addr.port);
			}
		private:
			addr_v6 m_addr;
		}
#endif
	};//namespace ip_address
};//namespace endpoint



#if 0


/* IPv6 address */
struct in6_addr
  {
    union
      {
        uint8_t __u6_addr8[16];
#if defined __USE_MISC || defined __USE_GNU
        uint16_t __u6_addr16[8];
        uint32_t __u6_addr32[4];
#endif
      } __in6_u;
#define s6_addr                 __in6_u.__u6_addr8
#if defined __USE_MISC || defined __USE_GNU
# define s6_addr16              __in6_u.__u6_addr16
# define s6_addr32              __in6_u.__u6_addr32
#endif
  };

#endif