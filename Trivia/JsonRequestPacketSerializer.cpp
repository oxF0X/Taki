#include "JsonRequestPacketSerializer.h"

std::vector<std::uint8_t> JsonRequestPacketSerializer::serializeResponse(ErrorResponse err)
{
    nlohmann::json j = err;
    return buildMsg(j, ERROR_RES);
}

std::vector<std::uint8_t> JsonRequestPacketSerializer::serializeResponse(LoginResponse l)
{
    nlohmann::json j = l;
    return buildMsg(j, LOGIN_RES);
}

std::vector<std::uint8_t> JsonRequestPacketSerializer::serializeResponse(SignupResponse s)
{
    nlohmann::json j = s;
    return buildMsg(j, SIGNUP_RES);
}


std::vector<uint8_t> JsonRequestPacketSerializer::buildMsg(nlohmann::json j, unsigned int id)
{
    std::vector<uint8_t> data = nlohmann::json::parse(std::string(j));
    std::vector<uint8_t> msg;
    std::vector<uint8_t> data_size = Helper::intToBytes(data.size());
    msg.push_back(id);
    std::copy(data_size.begin(), data_size.end(), std::back_inserter(msg));
    std::copy(data.begin(), data.end(), std::back_inserter(msg));
    return msg;
}
