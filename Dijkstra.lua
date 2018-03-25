-- dijkstra 算法
local G = {
	A = {B = 6, C = 3},
	B = {A = 6, C = 2, D = 5},
	C = {A = 3, B = 2, D = 3, E = 4},
	D = {B = 5, C = 3, E = 2, F = 3},
	E = {C = 4, D = 2, F = 5},
	F = {E = 5, D = 3},
	G = {H = 3},
}

local shortest = {};
local notSure = {};

-- 每条路径的结构，shortest和notSure的元素
function Record(name, path, dis)
	local o = {};
	o.name = name;
	o.path = path;
	o.dis = dis;
	return o;
end

-- 根据开始点产生所有最短路线
function DijkstaStartWith(start)
	if (not G[start]) then
		print("没有这个点");
		return
	end
	-- 初始化
	shortest = {};
	notSureList = {};
	for k, v in pairs(G) do
		local  path;
		if (k == start) then
			path = Record(k, {}, 0);
		else
			path = Record(k);
		end
		notSureList[k] = path;
	end

	while GetKLength(notSureList)>0 do
		-- 在notSureList中距离最短的路径可以确认为最短路线
		-- 把这条记录转移到已确定列表中
		local record = GetShortestRecord(notSureList);
		if (not record) then
			print("无法到达notSureList中剩余的任何点")
			break
		end
		shortest[record.name] = record;
		notSureList[record.name] = nil;
		Relax(record, notSureList);
	end
	-- print shortest
	for k, v in pairs(shortest) do
		local str = tostring(k).."->"..PrintArray(v.path).."->"..v.dis;
		print(str);
	end
end

function GetKLength(tbl)
	local num = 0;
	for k, v in pairs(tbl) do
		num = num + 1;
	end
	return num;
end

function GetShortestRecord(notSureList)
	local min = 999999;
	local flag;
	for k, v in pairs(notSureList) do
		if (v.dis and v.dis < min) then
			min = v.dis;
			flag = k;
		end
	end
	return notSureList[flag];
end

function Relax(curRecord, notSureList)
	local neighbor = G[curRecord.name];
	for k, v in pairs(neighbor) do
		-- 仅遍历未确定最短路径的点
		if (notSureList[k]) then
			-- 如果是第一次发现路线，或者新的路线如果消耗更小则覆盖
			if (not notSureList[k].path or (notSureList[k].dis > curRecord.dis + v)) then
				notSureList[k].path = MergeArray(curRecord.path, k);
				notSureList[k].dis = curRecord.dis + v;
			end
		end
	end
end

function MergeArray(list, value)
	local res = {};
	for i = 1, #list do
		table.insert(res, list[i]);
	end
	table.insert(res, value);
	return res;
end

function PrintDict(list)
	local str = "";
	for k, v in pairs(list) do
		str = str..tostring(k).." -> ";
		str = str..tostring(v).."\n";
	end
	print(str);
	return str;
end

function PrintArray(list)
	local str = "[";
	for i = 1, #list do
		str = str..list[i];
		if (i ~= #list) then
			str = str..","
		end
	end
	str = str.."]"
	-- print(str);
	return str;
end

DijkstaStartWith("A")