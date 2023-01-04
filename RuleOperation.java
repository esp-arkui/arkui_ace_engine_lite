package com.huawei.operation;

import com.huawei.entity.vo.projectmanagement.ProjectRuleVo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.data.mongodb.core.MongoTemplate;
import org.springframework.data.mongodb.core.query.Criteria;
import org.springframework.data.mongodb.core.query.Query;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
public class RuleOperation {
    @Autowired
    @Qualifier("codeCheckMongoTemplate")
    private MongoTemplate mongoTemplate;

    /**
     * 根据规则名称查询规则
     *
     * @param ruleName 规则名称
     * @return 满足条件的规则
     */
    public List<ProjectRuleVo> selectByRuleName(String ruleName) {
        Query query = Query.query(Criteria.where("ruleName").is(ruleName));
        return mongoTemplate.find(query, ProjectRuleVo.class);
    }
}
