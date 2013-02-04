#!/usr/bin/env ruby -w
# encoding: UTF-8
require "rubygems"
require "bundler/setup"
require "rspec"
require "json"
require "rr"
require File.dirname(__FILE__) + "/../sit"
include Sit

describe "Query" do
  it "should be to_s" do
    term = Term.new("hello", "world", 0)
    cj = Conjunction.new([term])
    cb = Callback.new(String, proc{})
    q = Query.new([cj], cb)
    q.to_s.should =~ /<\(hello ~ world\) cb:\d+>/
  end

	it "should be sorted" do
    a = Term.new("hello", "world", 0)
    b = Term.new("goodbye", "world", 0)
    cb = Callback.new(String, proc{})
    cj1 = Conjunction.new([a,b])
    cj2 = Conjunction.new([b,a])
    cj1.to_s.should == "(goodbye ~ world AND hello ~ world)"
    qa = Query.new([cj1], cb)
    qa.to_s
    
    qa = Query.new([cj1], cb)
    qb = Query.new([cj2], cb)
    qa.to_s.should == qb.to_s
    qa.to_s.should =~ /<\(goodbye ~ world AND hello ~ world\) cb:\d+>/
	end
end