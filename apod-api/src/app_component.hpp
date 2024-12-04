#ifndef api_AppComponent_hpp
#define api_AppComponent_hpp

#include "constants.hpp"
#include "swagger_component.hpp"

#include "oatpp/core/macro/component.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/network/virtual_/server/ConnectionProvider.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/web/server/HttpRouter.hpp"


namespace APOD::API {
	/* host: localhost, port: 8000 */
	struct HostAddress {
		oatpp::String host;
		v_uint16 port;
	};

	class AppComponent {
	private:
		HostAddress m_localHost;
		HostAddress m_virtualHost;

	public:
		explicit AppComponent(const HostAddress& local, const HostAddress virtualHost)
			: m_localHost(local), m_virtualHost(virtualHost) {
		};

		SwaggerComponent swagger;

		/**
		* The API VirtualHost interface
		*/
		OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, virtualInterface)(Definitions::API_SERVICE_NAME, [this] {

			return oatpp::network::virtual_::Interface::obtainShared(m_virtualHost.host);
			} ());

		/**
		* The real port connection provider
		*/
		OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)(Definitions::API_SERVICE_NAME, [this] {

			return oatpp::network::tcp::server::ConnectionProvider::createShared({ m_localHost.host, m_localHost.port });
			}());

		/**
		* The virtual host connection provider
		*/
		OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, virtualConnectionProvider) (Definitions::API_SERVICE_VH, [] {
			OATPP_COMPONENT(std::shared_ptr<oatpp::network::virtual_::Interface>, interface, Definitions::API_SERVICE_NAME);

			return oatpp::network::virtual_::server::ConnectionProvider::createShared(interface);
			} ());

		/**
		 *  Create Router component
		 */
		OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)(Definitions::API_SERVICE_NAME, [] {

			return oatpp::web::server::HttpRouter::createShared();
			}());

		/**
		 *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
		 */
		OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)(Definitions::API_SERVICE_NAME, [] {

			return oatpp::parser::json::mapping::ObjectMapper::createShared();
			}());
	};
}
#endif // !api_AppComponent_hpp
