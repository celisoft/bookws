#include "oatpp/web/server/HttpConnectionHandler.hpp"

#include "oatpp/network/Server.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"

#include "ServiceComponent.hpp"
#include "dto/MessageDTO.hpp"

/**
 * Custom Request Handler
 */
class Handler : public oatpp::web::server::HttpRequestHandler {
private:
	std::shared_ptr<oatpp::data::mapping::ObjectMapper> m_objectMapper;

public:
	/**
	 * Constructor with object mapper.
	 * @param objectMapper - object mapper used to serialize objects.
	 */
	Handler(const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& objectMapper)
		: m_objectMapper(objectMapper)
	{}

	/**
	 * Handle incoming request and return outgoing response.
	 */
	std::shared_ptr<OutgoingResponse> handle(const std::shared_ptr<IncomingRequest>& request) override {
		auto message = MessageDTO::createShared();
		message->statusCode = 1024;
		message->message = "Hello world!";
		return ResponseFactory::createResponse(Status::CODE_200, message, m_objectMapper);
	}

};

void run() {
	/* Create json object mapper */
	auto jsonObjectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();

	/* Create Router for HTTP requests routing */
	auto router = oatpp::web::server::HttpRouter::createShared();

	/* Route GET - "/hello" requests to Handler */
	router->route("GET", "/hello", std::make_shared<Handler>(jsonObjectMapper));

	/* Create HTTP connection handler with router */
	auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);

	/* Create TCP connection provider */
	auto connectionProvider = oatpp::network::tcp::server::ConnectionProvider::createShared({ "localhost", 8000, oatpp::network::Address::IP_4 });

	/* Create server which takes provided TCP connections and passes them to HTTP connection handler */
	oatpp::network::Server server(connectionProvider, connectionHandler);

	/* Print info about server port */
	OATPP_LOGI("BookWS", "Server running on port %s", connectionProvider->getProperty("port").getData());

	/* Run server */
	server.run();
}

int main() {

	/* Init oatpp Environment */
	oatpp::base::Environment::init();

	/* Run App */
	run();

	/* Destroy oatpp Environment */
	oatpp::base::Environment::destroy();

	return 0;

}

