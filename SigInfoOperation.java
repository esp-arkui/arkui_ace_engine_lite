package com.huawei.operation;

import com.huawei.entity.vo.codecheck.sigInfo.SigInfo;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.data.mongodb.core.MongoTemplate;
import org.springframework.data.mongodb.core.query.Criteria;
import org.springframework.data.mongodb.core.query.Query;
import org.springframework.stereotype.Component;

@Slf4j
@Component
public class SigInfoOperation {
    @Autowired
    @Qualifier("codeCheckMongoTemplate")
    private MongoTemplate mongoTemplate;

    //查询的表为Sin_Info表
    public SigInfo getSigInfoByRepoNameEn(String repoNameEn) {
        Query query = new Query(Criteria.where("repo_name_en").is(repoNameEn));
        return mongoTemplate.findOne(query, SigInfo.class);
    }
}
