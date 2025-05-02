# frozen_string_literal: true

require 'net/http'
require 'json'
require_relative 'auth_db'

response_data = Hmac.call
uri = URI('http://127.0.0.1:8000/verify') # replace later with the FastAPI VM IP

http = Net::HTTP.new(uri.host, uri.port)
request = Net::HTTP::Post.new(uri.path, {
                                'Content-Type' => 'application/json',
                                'X-HMAC-Signature' => response_data[:signature]
                              })

request.body = {
  mac_address: response_data[:mac_address],
  timestamp: response_data[:timestamp]
}.to_json

response = http.request(request)

puts "Response Code: #{response.code}"
puts "Response Code: #{response.body}"
